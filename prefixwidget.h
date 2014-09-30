#ifndef PREFIXPOLICY_H
#define PREFIXPOLICY_H

#include <QtWidgets/QComboBox>

class QLayout;

/**
 * @class PrefixWidget
 * @brief Base class of Prefix classes.
 */
class PrefixWidget  : public QComboBox {
	Q_OBJECT

	public:
		PrefixWidget(QWidget *parent = nullptr);

		virtual double indexToExponent(uint index) = 0;
		virtual int    exponentToIndex(uint exponent) = 0;
		/**
		 * @brief Transform the number to an "integral" form (i.e. 314159) to a "floatting" form (i.e. 3.14159×10⁵)
		 * @param value The value to transform
		 * @param exponent An exponent to compute
		 */
		virtual void   formatNumber(double &value, int &exponent) = 0;

};

/**
 * @class PrefixNone
 */
class PrefixNone : public PrefixWidget {
	Q_OBJECT

	public:
		PrefixNone(QWidget *parent = nullptr);

		virtual double indexToExponent(uint index);
		virtual int    exponentToIndex(uint exponent);
		virtual void   formatNumber(double &value, int &exponent);

};

/**
 * @class PrefixPow3
 */
class PrefixPow3 : public PrefixWidget {
	Q_OBJECT

	public:
		PrefixPow3(QWidget *parent = nullptr);

		virtual double indexToExponent(uint index);
		virtual int    exponentToIndex(uint exponent);
		virtual void   formatNumber(double &value, int &exponent);

};

/**
 * @class PrefixAll
 */
class PrefixAll  : public PrefixWidget {
	Q_OBJECT

	public:
		PrefixAll(QWidget *parent = nullptr);

		virtual double indexToExponent(uint index);
		virtual int    exponentToIndex(uint exponent);
		virtual void   formatNumber(double &value, int &exponent);

};

#endif // PREFIXPOLICY_H
