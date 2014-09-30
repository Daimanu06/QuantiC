#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "homewidget.h"
#include <QtWidgets/QAbstractButton>

class Quantity;

/**
 * @class ListButton
 * @ingroup GUI
 * @brief Button used in ListWidget.
 *
 * @warning Should not be directly used.
 * @see ListWidget
 */
class ListButton : public QAbstractButton {
	Q_OBJECT

	public:
		ListButton(const QSize &, const Quantity &, QWidget *parent = nullptr);

	protected:
		void paintEvent(QPaintEvent *);

	private:
		const Quantity &m_quantity;

};

/**
 * @class ListWidget
 * @ingroup GUI
 * @brief One possible home view.
 *
 * Display the quantities in a vertical list with an icon and a text.
 * @see HomeWidget
 * @see TileWidget
 */
class ListWidget : public HomeWidget {
	Q_OBJECT

	public:
		explicit ListWidget(QWidget *parent = nullptr);

};

#endif // LISTWIDGET_H
