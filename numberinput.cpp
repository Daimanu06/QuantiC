#include "numberinput.h"
#include <QtGui/QDoubleValidator>

/***** DOUBLE VALIDATOR *****/
//Note: Unless I can test a lot of locale, the behaviour will remain with C locale
DoubleValidator::DoubleValidator(number_t min, number_t max, int decimals, QObject *parent) :
	QDoubleValidator(min, max, decimals, parent)
{
	setNotation(QDoubleValidator::StandardNotation);
}

QValidator::State DoubleValidator::validate(QString &s, int &) const {
	QLocale locale;

	//TODO: problem in range
	//TODO: deal with locale
	if (s.isEmpty() || s.at(0) == '0' || s.at(0) == locale.negativeSign() || s.at(0) ==locale.positiveSign())
	//if (s.isEmpty() || s.at(0) == locale.negativeSign())
		return QValidator::Intermediate;

	bool ok;
	double d = s.toDouble(&ok);
	//double d = locale.toDouble(s, &ok); //"," (coma) doesn't work properly on French locale

	if (ok && d >= bottom() && d <= top())
		return QValidator::Acceptable;
	else
		return QValidator::Invalid;
}

/***** NUMBER INPUT *****/
//TODO: define number of decimal
NumberInput::NumberInput(number_t min, number_t max, number_t default_value, QWidget *parent) :
	QLineEdit(parent),
	validator( new DoubleValidator(min, max, 10, this) )
{
	setValue( default_value );

	setValidator(validator);
	connect(  this, &NumberInput::textChanged, [&](const QString &str){ emit valueChanged( str.toDouble() ); }  );
}

void NumberInput::setValue(number_t val) {
	setText( QString::number(val, 'g', 10) );
	//setText( QLocale().toString(val, 'g', 10));
}

NumberInput::number_t NumberInput::value() const {
	return text().toDouble();
}
