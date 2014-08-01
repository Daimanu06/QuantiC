#ifndef TILEWIDGET_H
#define TILEWIDGET_H

#include "data.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QAbstractButton>

class QSignalMapper;
class Banner;

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
 * @brief One of the two home widget.
 *
 * Display the quantities icons in a expandable grid.
 * @see StackedWidget
 * @see ListWidget
 */
class TileWidget : public QWidget {
	Q_OBJECT

	public:
		explicit TileWidget(const Banner *, QWidget *parent = nullptr);

	private:
		QSignalMapper *m_mapper;
};

#endif // TILEWIDGET_H
