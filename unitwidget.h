#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QtWidgets/QWidget>
#include "prefixwidget.h"
#include "data.h"

class NumberInput;
class QLabel;
class Unit;

/**
 * @class UnitWidget
 * @ingroup GUI
 * @brief represents one Unit.
 *
 * LineEdit, ComboBox and Label in a horizontal layout.
 */
class UnitWidget : public QWidget {
	Q_OBJECT

	public:
		explicit UnitWidget(const Unit &unit, bool prefixesAllowed, QWidget *parent = nullptr);

	signals:
		void valueChanged(double);
		void valueChanged(QString&);

	public slots:
		void setValue(double value);
		void prefixChanged();

	public:
		/**
		 * @fn value
		 * Returns the value computed from input's values (number from lineEdit and exponent from comboBox).
		 * @return the value computed.
		 */
		double value() const;

	private:
		NumberInput  *ui_numinput;
		PrefixWidget *ui_prefixes;
		QLabel       *ui_label;
		const Unit   &unit;

};

#endif // UNITWIDGET_H
