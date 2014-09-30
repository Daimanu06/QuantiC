#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QtWidgets/QWidget>
#include "prefixwidget.h"

class NumberInput;
class QLabel;
class Unit;

/**
 * @class UnitWidget
 * @ingroup GUI
 * @brief Widget representing an Unit.
 *
 * LineEdit, ComboBox and Label in a horizontal layout.
 */
class UnitWidget : public QWidget {
	Q_OBJECT

	public:
		explicit UnitWidget(const Unit &unit, bool prefixesAllowed, QWidget *parent = nullptr);

	signals:
		void valueChanged(double);   ///<Emitted when the value or the prefix has changed.
		void valueChanged(QString&); ///<Emitted when the value or the prefix has changed.

	public slots:
		void setValue(double value);
		void prefixChanged();

	public:
		/**
		 * @brief Returns the value computed with the value and the prefix.
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
