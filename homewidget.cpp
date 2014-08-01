#include "homewidget.h"
#include "settings.h"
#include "tilewidget.h"
#include "listwidget.h"
#include "banner.h"

HomeWidget::HomeWidget(QWidget *parent) :
	QScrollArea(parent)
{
	setWidgetResizable(true);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	//TODO changer l'accueil (i.e. réfléchir à l'architecture banner/stackedwidget
	/*
	connect(&Settings::getInstance(), &Settings::homeLayoutChanged, this, [&](Settings::HomeLayout layout) {
		takeWidget()->deleteLater();
	});
	*/
}

void HomeWidget::reloadData(Banner *banner) {
	Settings& settings = Settings::getInstance();

	if(settings.homeLayout() == Settings::H_List)
		setWidget(new ListWidget(banner, this));
	else
		setWidget(new TileWidget(banner, this));
}
