#include "listwidget.h"
#include "datamanager.h"
#include <QtCore/QSignalMapper>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QFont>

ListButton::ListButton(const QSize &fixed_size, const Quantity& q, QWidget *parent) :
	QAbstractButton(parent),
	m_quantity(q)
{
	setFixedSize(fixed_size);
	setToolTip(m_quantity.name);
	setCursor(Qt::PointingHandCursor);
}

void ListButton::paintEvent(QPaintEvent *event) {
	if( m_quantity.image.isNull() )
		return;

	QPainter p(this);
	p.drawPixmap( rect(), m_quantity.image.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation) );
	event->accept();
}

ListWidget::ListWidget(QWidget *parent) :
	HomeWidget(parent)
{
	DataManager& manager = DataManager::getInstance();
	QGridLayout *layout = new QGridLayout(this);
	const QSize  button_size(64, 64);

	auto toSentenceCase = [&](QString str) {
		str    = str.toLower();
		str[0] = str[0].toUpper();
	};

	//Set ListWidget and its children's font
	QFont font;
	font.setPointSize(15);
	setFont(font);

	//Set all the widgets
	for(int i = 0; i < manager.count(); i++) {
		ListButton *button = new ListButton(button_size, manager.at(i), this);
		QString name = manager.at(i).name;
		toSentenceCase(manager.at(i).name);
		QPushButton *text = new QPushButton(name);
		text->setStyleSheet("text-align:left; font-size: 16pt;");
		text->setFlat(true);
		layout->addWidget(button, i, 0);
		layout->addWidget(text, i, 1);
		connect(button, SIGNAL(clicked()), m_mapper, SLOT(map()));
		connect(text,   SIGNAL(clicked()), m_mapper, SLOT(map()));
		m_mapper->setMapping(button, i+1);
		m_mapper->setMapping(text, i+1);
	}

	connect(m_mapper, SIGNAL(mapped(int)), this, SIGNAL(quantityChosen(int)));
	setLayout(layout);
}
