#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QtWidgets/QScrollArea>

class Banner;

/**
 * @class HomeWidget
 * @ingroup GUI
 * @brief First page that shows a list of quantities.
 */
class HomeWidget : public QScrollArea {
	Q_OBJECT

	public:
		explicit HomeWidget(QWidget *parent = nullptr);

		void reloadData(Banner *);

};

#endif // HOMEWIDGET_H
