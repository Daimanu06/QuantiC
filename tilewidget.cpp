#include "tilewidget.h"
#include "tilelayout.h"
#include "banner.h"
#include "datamanager.h"
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtCore/QSignalMapper>
#include <QtGui/QPixmap>

TileButton::TileButton(const QSize& button_size, const Quantity &quantity, QWidget *parent) :
	QAbstractButton(parent),
	m_quantity(quantity)
{
	setFixedSize(button_size);
	setToolTip(m_quantity.name);
	setCursor(Qt::PointingHandCursor);
}

void TileButton::paintEvent(QPaintEvent *event) {
	if( m_quantity.image.isNull() )
		return;

	QPainter p(this);
	p.drawPixmap( rect(), m_quantity.image.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation) );
	event->accept();
}


TileWidget::TileWidget(QWidget *parent) :
	HomeWidget(parent)
{

	const QSize button_size(128, 128);
	TileLayout *layout = new TileLayout(button_size, this);
	DataManager &manager = DataManager::getInstance();

	for(int i = 0; i < manager.count(); i++) {
		TileButton *button = new TileButton(button_size, manager.at(i), this);
		layout->addWidget(button);
		connect(button, SIGNAL(clicked()), m_mapper, SLOT(map()));
		m_mapper->setMapping(button, i+1);
	}

	connect(m_mapper, SIGNAL(mapped(int)), this, SIGNAL(quantityChosen(int)));

	setLayout(layout);
}

