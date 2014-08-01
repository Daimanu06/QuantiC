#include "centralwidget.h"
#include "banner.h"
#include "stackedwidget.h"
#include <QtWidgets/QVBoxLayout>

CentralWidget::CentralWidget(QWidget *parent) :
	QWidget(parent),
	ui_bn  ( new Banner(this) ),
	ui_sw  ( new StackedWidget(this) )
{
	QVBoxLayout *ui_layout = new QVBoxLayout(this);

	ui_layout->addWidget(ui_bn);
	ui_layout->addWidget(ui_sw);

	connect(ui_bn, &Banner::currentIndexChanged, ui_sw, &StackedWidget::setCurrentIndex);

	ui_bn->setCurrentIndex( 0 );

	setLayout(ui_layout);
}

void CentralWidget::reloadData() {
	ui_bn->reloadData();
	ui_sw->reloadData(ui_bn);

	QWidget::update();
}
