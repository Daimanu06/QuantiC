#ifndef TILEWIDGET_H
#define TILEWIDGET_H

#include "data.h"
#include "homewidget.h"
#include <QtWidgets/QAbstractButton>

class Banner;

/**
 * @class TileButton
 * @ingroup GUI
 * @brief Button used in TileWidget.
 *
 * @warning Should not be directly used.
 * @see TileWidget
 */
class TileButton : public QAbstractButton {
	Q_OBJECT

	public:
		explicit TileButton(const QSize &, const Quantity&, QWidget *parent = nullptr);

	protected:
		void paintEvent(QPaintEvent *);

	private:
		Quantity m_quantity;

};

/**
 * @class TileWidget
 * @brief One possible home view.
 *
 * Display the quantities icons in a expandable grid.
 * @see StackedWidget
 * @see ListWidget
 */
class TileWidget : public HomeWidget {
	Q_OBJECT

	public:
		explicit TileWidget(QWidget *parent = nullptr);
};

#endif // TILEWIDGET_H
