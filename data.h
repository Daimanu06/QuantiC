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
 * It can be a base unit (one by quantity) or a derived unit (convertible to base unit).
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
		 * @brief Name of the unit.
		 *
		 * Loaded from the localized data file.
		 */
		QString name;

		/**
		 * @brief Pair of symbols, ASCII and Unicode.
		 *
		 * If the Unicode symbol doesn't exits, it is replaced with the ASCII symbol.
		 */
		QString symbols[2];

		/**
		 * @brief Default value of the unit.
		 *
		 * The base unit is always initialized to 0, the others units are initialized with fromBaseUnit(0).
		 */
		value_t defaultvalue;

		/**
		 * @brief Maximum value the unit cannot exceed.
		 *
		 * These values may not be reached.
		 * Inputs set their maximum values from these variables.
		 */
		value_t maximum =  1e50;

		/**
		 * @brief Minimum value the unit cannot exceed.
		 *
		 * i.e. A temperature value can theoretically not be lesser than absolute zero.
		 * These values may not be reached.
		 * Inputs set their minimum values from these variables.
		 */
		value_t minimum = -1e50;

	private:
		/**
		 * @brief Contains operations and constants to convert a value from derived unit to base unit.
		 *
		 * The opposite conversion (base to derived) is the inverse operations (reverse type and order).
		 * i.e. \f$y = ((x \times o_1) + o_2) / o_3 \equiv x = ((y \times o_3) - o_2) + o_1\f$
		 */
		QList< QPair<Operation, value_t> > toBase;

};


/**
 * @class Quantity
 * @ingroup Data
 * @brief Set of Units.
 *
 * A quantity have a name and an icon.
 * Behaves like a STL standard container.
 */
class Quantity : private QList<Unit> {
	public:
		typedef QList<Unit> Units;
		typedef Units::ConstIterator Iterator;

	public:
		Quantity( const QString& name, const QPixmap& image );
		/**
		 * @brief Name of the quantity.
		 *
		 * Loaded from the localized data file.
		 */
		QString name;
		/**
		 * @var image
		 *
		 * @brief A picture displayed in the home screen and in the banner.
		 */
		QPixmap image;
		/**
		 * @brief Some quantities shall not be prefixed.
		 *
		 * i.e. A prefixed temperature like "-40m°F" would make no sense.
		 */
		bool    prefixAllowed;

	public: //STL-like interface
        using QList<Unit>::begin;
        using QList<Unit>::end;
        using QList<Unit>::push_back;
        using QList<Unit>::count;
        using QList<Unit>::operator [];
        using QList<Unit>::at;

	private:
		Units units;

};

#endif // DATA_H
