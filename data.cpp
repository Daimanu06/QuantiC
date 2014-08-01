#include "data.h"
#include <functional> //std::function

typedef std::function<Unit::value_t(Unit::value_t, Unit::value_t)> operate;

/*****      UNIT      *****/
void Unit::addOperationToBase(Unit::Operation type, value_t value) {
	toBase.push_back( qMakePair(type, value) );
}
Unit::value_t Unit::toLegalUnit(value_t param) {
	operate op[] = {
		[](Unit::value_t a, Unit::value_t b) {return a + b;},
		[](Unit::value_t a, Unit::value_t b) {return a - b;},
		[](Unit::value_t a, Unit::value_t b) {return a * b;},
		[](Unit::value_t a, Unit::value_t b) {return a / b;}
	};
	for(const auto& pair : toBase)
		param = op[pair.first](param, pair.second);
	return param;
}
Unit::value_t Unit::fromBaseUnit(value_t param) {
	operate op[] = {
		[](Unit::value_t a, Unit::value_t b) {return a - b;},
		[](Unit::value_t a, Unit::value_t b) {return a + b;},
		[](Unit::value_t a, Unit::value_t b) {return a / b;},
		[](Unit::value_t a, Unit::value_t b) {return a * b;}
	};

	//inverse of toBaseUnit operations
	auto pair = toBase.constEnd();
	while(pair != toBase.constBegin()) {
		--pair;
		param = op[pair->first](param, pair->second);
	}
	return param;
}

/*****    QUANTITY    *****/
Quantity::Quantity(const QString& name, const QPixmap& image) :
	name(name),
	image(image)
{}
Quantity::Iterator Quantity::begin() const noexcept {
	return units.begin();
}
Quantity::Iterator Quantity::end() const noexcept {
	return units.end();
}
void Quantity::push_back(const Unit &u) {
	units.push_back(u);
}
int Quantity::count() const noexcept {
	return units.count();
}
const Quantity::value_type &Quantity::at(int i) const {
	return units.at(i);
}
Unit& Quantity::operator [] (int i) {
	return units[i];
}
