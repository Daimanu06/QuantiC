#ifndef SPINBOX_H
#define SPINBOX_H

#include <QtWidgets/QLineEdit>
#include <QtGui/QDoubleValidator>

/**
 * Redefine the rules of the validator since the QDoubleValidator behaviour is weird to me.
 */
class DoubleValidator : public QDoubleValidator {
	Q_OBJECT
	public:
		typedef double number_t;
		DoubleValidator(number_t min, number_t max, int decimals, QObject *parent = nullptr);
		~DoubleValidator() = default;
		QValidator::State validate(QString &, int &) const;
};

/**
 * @class NumberInput
 * @brief Gets the input from the user.
 *
 * Validates the format of the number (see QLocale).
 */
class NumberInput : public QLineEdit {
	Q_OBJECT

	public:
		typedef double number_t;

	public:
		explicit NumberInput(number_t min, number_t max, number_t default_value, QWidget *parent = nullptr);

	public:
		void  setValue(number_t val);
		number_t value() const;

	signals:
		void valueChanged(double);

	public:
		QDoubleValidator *validator;

};

#endif // SPINBOX_H
