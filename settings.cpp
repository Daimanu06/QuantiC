#include "settings.h"
#include <QtCore/QCoreApplication>

Settings& Settings::getInstance() {
	static Settings instance;
	return instance;
}

Settings::Settings() :
	QObject(),
	qs(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName())
{
	qs.beginGroup("window");
	window_geometry       = qs.value("window-geo",  QRect(470, 200, 500, 500)).toRect();
	window_maximized      = qs.value("window-maxi", false).toBool();
	window_geometry_saved = qs.value("window-save", true).toBool();
	qs.endGroup();

	qs.beginGroup("directories");
	data_dir  = qs.value("data",  QCoreApplication::applicationDirPath()+"/data" ).toString();
	qs.endGroup();

	qs.beginGroup("home");
	home_layout = HomeLayout(qs.value("home-screen", H_Grid).toUInt());
	qs.endGroup();

	qs.beginGroup("other");
	symbol_type = SymbolType(qs.value("symbol-type", S_ASCII).toUInt());
	prefix_policy = PrefixPolicy(qs.value("prefix-policy", P_OnlyPow3).toUInt());
	qs.endGroup();
}

Settings::~Settings() {
	qs.beginGroup("window");
	qs.remove("window-geo");
	qs.remove("window-maxi");
	qs.setValue("window-save", window_geometry_saved);

	if(window_geometry_saved) {
		qs.setValue("window-maxi", window_maximized);
		if( !window_maximized )
			qs.setValue("window-geo", window_geometry);
	}
	qs.endGroup();

	qs.beginGroup("directories");
	qs.setValue("data",  data_dir);
	qs.endGroup();

	qs.beginGroup("home");
	qs.setValue("home-screen", home_layout);
	qs.endGroup();

	qs.beginGroup("other");
	qs.setValue("symbol-type", symbol_type);
	qs.setValue("prefix-policy", prefix_policy);
	qs.endGroup();
}

/*** Getters ***/
QRect Settings::windowGeometry() const {
	return window_geometry;
}

bool Settings::isWindowMaximized() const {
	return window_maximized;
}

bool Settings::isWindowGeometrySaved() const {
	return window_geometry_saved;
}

Settings::SymbolType Settings::symbolType() const {
	return SymbolType(symbol_type % 2);
}

Settings::PrefixPolicy Settings::prefixPolicy() const {
	return PrefixPolicy(prefix_policy % 3);
}

Settings::HomeLayout Settings::homeLayout() const {
	return HomeLayout(home_layout % 2);
}

QString Settings::dataDirectory() const {
	return data_dir;
}


/*** Setters ***/
void Settings::setWindowGeometry(const QRect& geometry) {
	window_geometry = geometry;
}

void Settings::setWindowMaximized(bool maxi) {
	window_maximized = maxi;
}

void Settings::setWindowGeometrySaved(bool save) {
	window_geometry_saved = save;
}

void Settings::setSymbolType(int t) {
	SymbolType type = SymbolType(t % 2);
	if(symbol_type == type)
		return;
	symbol_type = type;
	emit symbolTypeChanged(type);
}

void Settings::setPrefixPolicy(int p) {
	PrefixPolicy policy = PrefixPolicy(p % 3);
	if(prefix_policy == policy)
		return;
	prefix_policy = policy;
	emit prefixPolicyChanged(policy);
}

void Settings::setHomeLayout(int l) {
	HomeLayout layout = HomeLayout(l % 2);
	if(home_layout == layout)
		return;
	home_layout = layout;
	emit homeLayoutChanged(layout);
}

void Settings::setDataDirectory(const QString &loc) {
	if(data_dir == loc)
		return;
	data_dir = loc;
	emit dataLocationChanged(loc);
}
