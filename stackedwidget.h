#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QtWidgets/QStackedWidget>

class Banner;

/**
 * @class StackedWidget
 * @ingroup GUI
 * @brief Contains the HomeWidget and a set of QuantityWidget
 */
class StackedWidget : public QStackedWidget {
	Q_OBJECT

	public:
		explicit StackedWidget(QWidget *parent = nullptr);

		void clear();

	public slots:
		void reloadData(Banner *);

};

#endif // STACKEDWIDGET_H
