#include "datamanager.h"
#include <QtCore/QHash>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtGui/QPixmap>
#include <QtXml/QDomDocument>

DataManager& DataManager::getInstance() {
	static DataManager instance;
	return instance;
}

void DataManager::loadQuantities(const QDir& data_dir) {
	if( !data_dir.exists() ) {
		qWarning( "Error: incorrect data path.\nNothing will be loaded." );
		return;
	}

	QFile order_file(data_dir.path() + "/order");
	order_file.open(QIODevice::ReadOnly | QIODevice::Text);
	if( !order_file.exists() ) {
		qWarning("Error: order file is missing.\nNothing will be loaded.");
		return;
	}

	QDir quantities_dir( data_dir.path() + "/quantities",  QString("*.xml"), QDir::Name, QDir::Files );
	QDir icons_dir     ( data_dir.path() + "/icons",       QString("*.png"), QDir::Name, QDir::Files );

	//Read order file
	QString line;
	while( !order_file.atEnd() ) {
		line = order_file.readLine();
		line.remove('\n');

		//Try to open icon
		QPixmap icon;
		QString icon_path = icons_dir.path() + '/' + line + ".png";
		if( !icon.load(icon_path) ) {
			qWarning( "Icon for \"%s\" was not found.", qPrintable(line) );
			icon.load(":/icon/no_icon");
		}

		//Try to open XML file.
		QFile file( quantities_dir.path() + '/' + line + ".xml" );
		if(  !file.open(QIODevice::ReadOnly | QIODevice::Text)  ) {
			qWarning( "Error:Cannot open quantity %s.", qPrintable(file.fileName()) );
			continue;
		}

		//Try to load XML file.
		QDomDocument document;
		QString err_s;
		int err_l = 0, err_c = 0;
		if(  !document.setContent(&file, false, &err_s, &err_l, &err_c)  ) {
			qWarning(  "In quantity \"%s:\" At line %i, column %i. %s", qPrintable(file.fileName()), err_l, err_c, qPrintable(err_s)  );
			continue;
		}

		quantities.push_back( loadQuantity( document, icon ) );
	}
	order_file.close();
}

Quantity DataManager::loadQuantity(const QDomDocument& xml_document, const QPixmap& pixmap) {
	// Start document parsing and variables setting
	QDomElement root = xml_document.documentElement();

	Quantity quantity( root.attribute("name"), pixmap);
	quantity.prefixAllowed = (root.attribute("prefixsAllowed") == "yes");

	// Treatment of <baseunit> tag
	Unit baseunit = loadBaseUnit(root.firstChildElement("baseunit"));
	quantity.push_back( baseunit );

	// Treatment of <unit> tags
	QDomElement unit_elem = root.firstChildElement("unit");
	while( !unit_elem.isNull() ) { //for each <unit> tag
		quantity.push_back( loadUnit(unit_elem, baseunit) );
		unit_elem = unit_elem.nextSiblingElement("unit");
	}

	qDebug("Quantity \"%s\" loaded.", qPrintable(root.attribute("name")));
	return quantity;
}

Unit DataManager::loadBaseUnit(const QDomElement& base_unit_element) {
	Unit baseunit;

	QString     name     = base_unit_element.attribute("name");
	QString     symbol_a = base_unit_element.firstChildElement( "symbols" ).firstChildElement("ascii").text();
	QString     symbol_u = base_unit_element.firstChildElement( "symbols" ).firstChildElement("unicode").text();
	QDomElement min      = base_unit_element.firstChildElement( "minimum" );
	QDomElement max      = base_unit_element.firstChildElement( "maximum" );

	double limit = 1e50; //GUI widgets will never go beyond this limit
	double minimum = (min.isNull() ? -limit : min.text().toDouble() );
	double maximum = (max.isNull() ?  limit : max.text().toDouble() );

	//Initialize baseUnit object
	baseunit.name         = name;
	baseunit.symbols[0]   = symbol_a;
	baseunit.symbols[1]   = symbol_u;
	baseunit.defaultvalue = 0;
	baseunit.minimum      = minimum;
	baseunit.maximum      = maximum;

	return baseunit;
}

Unit DataManager::loadUnit(const QDomElement &unit_element, const Unit &base_unit) {
	static QHash<QString, Unit::Operation> hash_operations; //necessary to translate operations like "<plus>5</plus>" to "+5"
	hash_operations["plus"]    = Unit::PLUS;
	hash_operations["less"]    = Unit::LESS;
	hash_operations["times"]   = Unit::TIMES;
	hash_operations["divided"] = Unit::DIVIDED;

	Unit unit;

	QString name     = unit_element.attribute("name");
	QString symbol_a = unit_element.firstChildElement( "symbols" ).firstChildElement("ascii").text();
	QString symbol_u = unit_element.firstChildElement( "symbols" ).firstChildElement("unicode").text();
	unit.name   = name;
	unit.symbols[0] = symbol_a;
	unit.symbols[1] = symbol_u;

	//Load conversion operations to base unit
	QDomElement operations_element = unit_element.firstChildElement("tobase");
	QDomNode    op_node = operations_element.firstChild();

	while( !op_node.isNull() ) {
		QDomElement elem = op_node.toElement();
		unit.addOperationToBase(hash_operations[ elem.nodeName() ], elem.text().toDouble() );
		op_node = op_node.nextSibling();
	}

	//Initialize Unit object
	unit.defaultvalue = unit.fromBaseUnit(base_unit.defaultvalue);
	unit.minimum      = unit.fromBaseUnit(base_unit.minimum);
	unit.maximum      = unit.fromBaseUnit(base_unit.maximum);
	if(unit.minimum > unit.maximum) //Some units won't work without this line (i.e. Delisle degree, where 0°De is higher than 100°De)
		qSwap( unit.minimum, unit.maximum );

	return unit;
}

/***************** STL-like interface *****************/
bool DataManager::isempty() const noexcept {
	return quantities.empty();
}

DataManager::Iterator DataManager::begin() noexcept {
	return quantities.begin();
}

DataManager::Iterator DataManager::end() noexcept {
	return quantities.end();
}

int DataManager::count() const noexcept {
	return quantities.count();
}

const DataManager::value_type &DataManager::at(int i) const {
	return quantities.at(i);
}

void DataManager::clear() {
	quantities.clear();
}
