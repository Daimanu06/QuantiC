#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "data.h"
#include <QtCore/QList>

class QString;
class QDir;
class QDomDocument;
class QDomElement;

/**
 * @class DataManager
 * @ingroup Data
 * @brief Controller class (singleton).
 *
 * Interface to load quantities from file system according to user's locale.
 * Behaves like a C++ standard container of Quantities.
 */
class DataManager : private QList< Quantity > {
	public:
		typedef QList< Quantity > QuantityList;
		typedef QuantityList::Iterator Iterator;

	private: //ctor, dtor and operator=
		DataManager();
		DataManager(const DataManager&)  = delete;
		DataManager(      DataManager&&) = delete;
		~DataManager();
		DataManager& operator=(const DataManager&)  = delete;
		DataManager& operator=(      DataManager&&) = delete;

	public: //Singleton methods
		/**
		 * @fn getInstance
		 * Singleton method to manipulate only one instance of DataManager.
		 * @return Unique instance of DataManager.
		 */
		static DataManager& getInstance();

	public:
		/**
		 * @fn loadQuantities
		 * List, validate and load quantities files of the given directory.
		 * @param quantities_dir The directory that contains Quantities.
		 * @param icons_dir      The directory that contains icons.
		 */
		void loadQuantities(const QDir&, const QDir&);

	private: //Private loading functions
		/**
		 * @fn loadQuantity
		 * Parse given DOM tree to create a Quantity object.
		 * @param xml_document A valid XML Dom Tree.
		 * @param pixmap The picture to bind to the quantity.
		 * @return The newly Quantity object created.
		 */
		Quantity loadQuantity (const QDomDocument&, const QPixmap &);

		/**
		 * @fn loadBseUnit
		 * Parse given XML Element to create an Unit object.
		 * @param base_unit_element The loaded <baseunit> Element.
		 * @return The newly Unit object created.
		 */
		Unit     loadBaseUnit(const QDomElement &);

		/**
		 * @fn loadUnit
		 * Parse given XML Element to create an Unit object.
		 * @param unit_element The loaded <unit> Element.
		 * @param base_unit Baseunit object, to correctly initialize the returned Unit (maximum, minimum and default value).
		 * @return The newly Unit object created.
		 */
		Unit     loadUnit     (const QDomElement &, const Unit &);

	public: //STL-like interface
		bool        isempty() const noexcept;
		Iterator    begin()   noexcept;
		Iterator    end()     noexcept;
		int         count()   const noexcept;
		void        clear();
		const value_type& at(int i) const;

	private:
		QuantityList quantities;

};

#endif // DATAMANAGER_H
