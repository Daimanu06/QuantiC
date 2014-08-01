#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QAbstractButton>

class Banner;
class Quantity;
class QSignalMapper;

/**
 * @class ListButton
 * @ingroup GUI
 * @brief Button used in list layout.
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
 * @brief One of the two home widget.
 *
 * Display the quantities in a vertical list with an icon and a text.
 * @see HomeWidget
 * @see TileWidget
 */
class ListWidget : public QWidget {
	Q_OBJECT

	public:
		explicit ListWidget(const Banner *, QWidget *parent = nullptr);

	private:
		QSignalMapper  *m_mapper;

};

#endif // LISTWIDGET_H
