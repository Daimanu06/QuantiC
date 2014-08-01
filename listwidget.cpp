#include "listwidget.h"
#include "banner.h"
#include "datamanager.h"
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtCore/QSignalMapper>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

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


ListWidget::ListWidget(const Banner *banner, QWidget *parent) :
	QWidget(parent),
	m_mapper(new QSignalMapper(this))
{
	DataManager& manager = DataManager::getInstance();
	QGridLayout *layout = new QGridLayout(this);
	const QSize  button_size(64, 64);

	auto toSentenceCase = [&](QString str)->QString&{
		str    = str.toLower();
		str[0] = str[0].toUpper();
		return str;
	};
	for(int i = 0; i < manager.count(); i++) {
		ListButton *button = new ListButton(button_size, manager.at(i), this);
		layout->addWidget(button, i, 0);
		layout->addWidget(new QLabel(toSentenceCase(manager.at(i).name), this), i, 1);
		connect(button, SIGNAL(clicked()), m_mapper, SLOT(map()));
		m_mapper->setMapping(button, i+1);
	}

	connect(m_mapper, SIGNAL(mapped(int)), banner, SLOT(setCurrentIndex(int)));
	setLayout(layout);
}
