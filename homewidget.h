#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QtWidgets/QWidget>

class QSignalMapper;

/**
 * @class HomeWidget
 * @ingroup GUI
 * @brief Base class of home pages.
 *
 * @see TileWidget
 * @see ListWidget
 */
class HomeWidget : public QWidget {
	Q_OBJECT

	public:
		explicit HomeWidget(QWidget *parent = nullptr);

	signals:
		void quantityChosen(int);

	protected:
		QSignalMapper  *m_mapper;

};

#endif // HOMEWIDGET_H
