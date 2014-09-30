#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QScrollArea>
#include "settings.h"

class Banner;

/**
 * @class StackedWidgetHome
 * @brief First page of the StackedLayout.
 *
 * Changes dynamically its view when the settings "HomeLayout" changes.
 */
class StackedWidgetHome : public QScrollArea {
	Q_OBJECT

	public:
		StackedWidgetHome(QWidget *parent = nullptr);

	public slots:
		void setHomeLayout(Settings::HomeLayout); ///<Changes the home layout.

	signals:
		void quantityChosen(int);
};

/**
 * @class StackedWidget
 * @ingroup GUI
 * @brief Contains the HomeWidget and a set of QuantityWidget
 */
class StackedWidget : public QStackedWidget {
	Q_OBJECT

	public:
		explicit StackedWidget(QWidget *parent = nullptr);

		void removePages(); ///<Remove all the pages.

	public slots:
		void reloadData();

	signals:
		void quantityChosen(int);

};

#endif // STACKEDWIDGET_H
