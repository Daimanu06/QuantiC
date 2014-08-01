#ifndef DATA_H
#define DATA_H

#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtGui/QPixmap>

/**
 * @class Unit
 * @ingroup Data
 * @brief Unit is the basic data type of the converter.
 *
 * It may be a base unit (one by quantity) or a derived unit (convertible to base unit).
 * An unit has a name (i.e. "meter"), a symbol (i.e. "m"), a default, minimum and maximum value.
 */
class Unit {
	public:
		typedef double value_t;
		enum Operation {PLUS, LESS, TIMES, DIVIDED};

	public:
		void    addOperationToBase(Operation type, value_t value);
		value_t toLegalUnit       (value_t param);
		value_t fromBaseUnit      (value_t param);

	public:
		/**
		 * @var name
		 * @brief Name of the unit.
		 * Loaded from the data file.
		 */
		QString name;

		/**
		 * @var symbols
		 * @brief Pair of symbols, ASCII and Unicode (if available).
		 */
		QString symbols[2];

		/**
		 * @var defaultvalue
		 * @brief Default value of the unit.
		 * Base unit is always initialized to 0, other units with fromBaseUnit(0).
		 */
		value_t defaultvalue;

		/**
		 * @var maximum
		 * @brief Maximum value the unit cannot exceed.
		 * i.e. You can block a percentage to 100.
		 * These values may not be reached.
		 * Inputs set their own maximum values from these variables.
		 */
		value_t maximum =  1e50;

		/**
		 * @var minimum
		 * @brief Minimum value the unit cannot exceed.
		 * i.e. A temperature value can theoretically not be lesser than absolute zero.
		 * These values may not be reached.
		 * Inputs set their own minimum values from these variables.
		 */
		value_t minimum = -1e50;

	private:
		/**
		 * @var toBase
		 * @brief Contains operations and constants to convert a value from derived unit to base unit.
		 * The opposite conversion (base to derived) is the inverse operations type and order.
		 * i.e y = (((x×A)+B)÷C) ≡ x = (((y×C)−B)÷A)
		 */
		QList< QPair<Operation, value_t> > toBase;

};


/**
 * @class Quantity
 * @ingroup Data
 * @brief Set of Units. A quantity have a name and an icon.
 *
 * Behaves like a STL standard container.
 */
class Quantity : private QList<Unit> {
	public:
		typedef QList<Unit> Units;
		typedef Units::ConstIterator Iterator;

	public:
		Quantity( const QString& name, const QPixmap& image );
		/**
		 * @var name
		 * @brief Name of the quantity.
		 * Loaded from the localized data file.
		 */
		QString name;
		/**
		 * @var image
		 * @brief A picture displayed in the home screen and in the banner.
		 */
		QPixmap image;
		/**
		 * @var prefixAllowed
		 * @brief Some quantities shall not be prefixed.
		 * i.e. A prefixed temperature "-40m°F" would make no sense.
		 */
		bool    prefixAllowed;

	public: //STL-like interface
		Iterator begin() const noexcept;
		Iterator end()   const noexcept;
		void     push_back(const Unit &u);
		int      count() const noexcept;
		Unit&    operator [] (int);
		const value_type &at(int i) const;

	private:
		Units units;

};

#endif // DATA_H
