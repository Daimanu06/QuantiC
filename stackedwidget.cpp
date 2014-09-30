#include "stackedwidget.h"
#include "datamanager.h"
#include "settings.h"
#include "listwidget.h"
#include "tilewidget.h"
#include "quantitywidget.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>

/** StackedWidgetHome **/
StackedWidgetHome::StackedWidgetHome(QWidget *parent) :
	QScrollArea(parent)
{
	setWidgetResizable(true);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	connect(&Settings::getInstance(), &Settings::homeLayoutChanged, this, &StackedWidgetHome::setHomeLayout);
	setHomeLayout(Settings::getInstance().homeLayout());
}

void StackedWidgetHome::setHomeLayout(Settings::HomeLayout newlayout) {
	HomeWidget *wid;
	if(newlayout == Settings::H_List)
		wid = new ListWidget(this);
	else
		wid = new TileWidget(this);
	setWidget(wid);
	connect(wid, &HomeWidget::quantityChosen, this, &StackedWidgetHome::quantityChosen);
}

/** StackedWidget **/
StackedWidget::StackedWidget(QWidget *parent) :
	QStackedWidget(parent)
{}

void StackedWidget::removePages() {
	for(QWidget *widget : findChildren<QWidget*>(QString(), Qt::FindChildrenRecursively)) {
		removeWidget(widget);
		widget->deleteLater();
	}
}

void StackedWidget::reloadData() {
	removePages();

	DataManager& manager = DataManager::getInstance();

	if( manager.isempty() ) {
		addWidget( new QLabel(tr("No quantities found.")) );
		return;
	}

	//Home
	StackedWidgetHome *home = new StackedWidgetHome(this);
	addWidget(home);
	connect(home, &StackedWidgetHome::quantityChosen, this, &StackedWidget::quantityChosen);

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
