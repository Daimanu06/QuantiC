#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QtWidgets/QWidget>

class Banner;
class StackedWidget;

/**
 * @class CentralWidget
 * @ingroup GUI
 * @brief Central widget handled in the main window.
 *
 * Contains a Banner and a StackedWidget.
 */
class CentralWidget : public QWidget {
	Q_OBJECT

	public:
		explicit CentralWidget(QWidget *parent = nullptr);

	public:
		void reloadData();

	private:
		Banner        *ui_bn;
		StackedWidget *ui_sw;

};

#endif // CENTRALWIDGET_H
