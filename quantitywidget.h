#ifndef QUANTITY_WIDGET_H
#define QUANTITY_WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCore/QList>

class UnitWidget;
class QSignalMapper;
class UnitWidget;
class Quantity;

/**
 * @class QuantityWidget
 * @ingroup GUI
 * @brief This widget shows Units vertically.
 */
class QuantityWidget : public QWidget {
	Q_OBJECT

	public:
		explicit QuantityWidget(Quantity &quantity, QWidget *parent = nullptr);

	public slots:
		void aValueHasChanged(int);

	private:
		Quantity&           quantity;
		QSignalMapper      *mapper;
		QList<UnitWidget*>  units;
};

#endif // QUANTITY_WIDGET_H
