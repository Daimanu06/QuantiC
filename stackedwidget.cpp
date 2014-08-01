#include "stackedwidget.h"
#include "datamanager.h"
#include "settings.h"
#include "listwidget.h"
#include "tilewidget.h"
#include "quantitywidget.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include "homewidget.h"

StackedWidget::StackedWidget(QWidget *parent) :
	QStackedWidget(parent)
{}

void StackedWidget::clear() {
	for(QWidget *widget : findChildren<QWidget*>(QString(), Qt::FindChildrenRecursively))
		widget->deleteLater();

}

void StackedWidget::reloadData(Banner *banner) {
	clear();

	DataManager& manager = DataManager::getInstance();

	if( manager.isempty() ) {
		addWidget( new QLabel(tr("No quantities found.")) );
		return;
	}

	//Home
	HomeWidget *home = new HomeWidget(this);
	home->reloadData(banner);
	addWidget(home);

	//all quantities
	for(Quantity& quantity : manager) {
		QScrollArea *scroll = new QScrollArea(this);
		scroll->setWidgetResizable(true);
		scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		scroll->setWidget(new QuantityWidget( quantity, this ));
		addWidget(scroll);
	}

	QStackedWidget::update();
}
