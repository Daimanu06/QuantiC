#include "prefixwidget.h"
#include <cmath>
#include <limits>
#include <QtCore/QHash>
#include <QtWidgets/QLayout>

PrefixWidget::PrefixWidget(QWidget *parent) :
	QComboBox(parent)
{}


/***** PrefixNone *****/
PrefixNone::PrefixNone(QWidget *parent) :
	PrefixWidget(parent)
{}
double PrefixNone::indexToExponent(uint) {return 1;}
int    PrefixNone::exponentToIndex(uint) {return 0;}
void   PrefixNone::formatNumber(double &, int &) {}


/***** Only power of 3 *****/
PrefixPow3::PrefixPow3(QWidget *parent) :
	PrefixWidget(parent)
{
	static QString data[17][2] = {
		{"y", "yocto"},
		{"z", "zepto"},
		{"a", "atto"},
		{"f", "femto"},
		{"p", "pico"},
		{"n", "nano"},
		{u8"\302\265", "micro"},
		{"m", "milli"},
		{"-", ""},
		{"k", "kilo"},
		{"M", "mega"},
		{"G", "giga"},
		{"T", "tera"},
		{"P", "peta"},
		{"E", "exa"},
		{"Z", "zetta"},
		{"Y", "yotta"}
	};

	for(auto str : data) {
		addItem(str[0]);
		setItemData(currentIndex(), str[1], Qt::ToolTipRole);
	}
	setCurrentIndex(8);
}
double PrefixPow3::indexToExponent(uint index) {
	//return pow10((double)index*3-24);
	return pow(10, (double)index*3-24);
}
int PrefixPow3::exponentToIndex(uint exponent) {
	return (exponent+24)/3;
}
void PrefixPow3::formatNumber(double& value, int& exponent) {
	//qDebug("%i", (int)log10(value));//TODO: simplifier?

	//value = |value|
	// |value| = 0
	//Expected prefixe : none

	if(value == 0) {
		value = 0;
		exponent = 0;
		return;
	}
	// |value| ∈ [ 0; 10^-24]
	//Expected prefixe : y
	//May never be reached due to double limitations
	if( value >= 0 && value <= 1e-24 ) {
		exponent = -24;
		value *= 1e24;
		return;
	}
	// |value| ∈  [ 10^24; +∞ [
	//Expected prefixe : Y
	//May never be reached due to double limitations
	if( value >= 1e24 ) {
		exponent = 24;
		value /= 1e24;
		return;
	}

	// |value| ∈ ] 1000; +∞ [
	//Expected prefixes : k M G T P E Z
	while( value >= 1000 ) {
		exponent += 3;
		value /= 1000;
	}
	// |value| ∈ ] 1000; +∞ [
	//Expected prefixes : m µ n p f a z
	while( value >= 0 && value < 1 ) {
		exponent -= 3;
		value *= 1000;
	}
}


/***** All *****/
PrefixAll::PrefixAll(QWidget *parent) :
	PrefixWidget(parent)
{
	static QString data[21][2] = {
		{"y", "yocto"},
		{"z", "zepto"},
		{"a", "atto"},
		{"f", "femto"},
		{"p", "pico"},
		{"n", "nano"},
		{u8"\302\265", "micro"},
		{"m", "milli"},
		{"c", "centi"},
		{"d", "deci"},
		{"-", ""},
		{"da", "deca"},
		{"h", "hecto"},
		{"k", "kilo"},
		{"M", "mega"},
		{"G", "giga"},
		{"T", "tera"},
		{"P", "peta"},
		{"E", "exa"},
		{"Z", "zetta"},
		{"Y", "yotta"}
	};

	for(auto str : data) {
		addItem(str[0]);
		setItemData(currentIndex(), str[1], Qt::ToolTipRole);
	}
	setCurrentIndex(10);
}
double PrefixAll::indexToExponent(uint index) {
	static double indexToexp[] = {
		1e-24, 1e-21, 1e-18, 1e-15, 1e-12, 1e-9, 1e-6, 1e-3, 1e-2, 1e-1,
		1, 1e1, 1e2, 1e3, 1e6, 1e9, 1e12, 1e15, 1e18, 1e21, 1e24
	};
	return indexToexp[index];
}
int PrefixAll::exponentToIndex(uint exponent) {
	static QHash<int, uint> expToIndex({
		{-24,  0}, {-21,  1}, {-18,  2},
		{-15,  3}, {-12,  4}, { -9,  5},
		{ -6,  6}, { -3,  7}, { -2,  8},
		{ -1,  9}, {  0, 10}, {  1, 11},
		{  2, 12}, {  3, 13}, {  6, 14},
		{  9, 15}, { 12, 16}, { 15, 17},
		{ 18, 18}, { 21, 19}, { 24, 20}
	});
	return expToIndex[exponent];
}
void PrefixAll::formatNumber(double& value, int& exponent) {
	//value = |value|
	// |value| = 0
	//Expected prefixe : none
	if(value == 0) {
		value = 0;
		exponent = 0;
		return;
	}
	// |value| ∈ [ 0; 10^-24]
	//Expected prefixe : y
	//May never be reached due to double limitations
	if( value >= 0 && value <= 1e-24 ) {
		exponent = -24;
		value *= 1e24;
		return;
	}
	// |value| ∈  [ 10^24; +∞ [
	//Expected prefixe : Y
	//May never be reached due to double limitations
	if( value >= 1e24 ) {
		exponent = 24;
		value /= 1e24;
		return;
	}

	// |value| ∈ [ 0.001; 1 [
	//Expected prefixes : c d
	while( value >= 0.001 && value < 1 ) {
		exponent--;
		value *= 10;
	}
	// |value| ∈ [ 10; 1000 [
	//Expected prefixes : da h
	while( value >= 10 && value < 1000 ) {
		exponent++;
		value /= 10;
	}

	// |value| ∈ ] 1000; +∞ [
	//Expected prefixes : k M G T P E Z
	while( value >= 1000 ) {
		exponent += 3;
		value /= 1000;
	}
	// |value| ∈ ] 1000; +∞ [
	//Expected prefixes : m µ n p f a z
	while( value >= 0 && value < 1 ) {
		exponent -= 3;
		value *= 1000;
	}
}
