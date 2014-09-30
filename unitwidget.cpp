#include "unitwidget.h"
#include "numberinput.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include "settings.h"
#include "data.h"

UnitWidget::UnitWidget(const Unit &unit, bool prefixAllowed, QWidget *parent) :
	QWidget( parent ),
	ui_numinput ( new NumberInput( unit.minimum, unit.maximum, unit.defaultvalue) ),
	ui_label    ( new QLabel     ( unit.symbols[Settings::getInstance().symbolType()] ) ),
	unit        ( unit )
{
	QHBoxLayout *layout = new QHBoxLayout;
	ui_numinput->setMinimumWidth(300);
	ui_label->setFixedWidth(50);

	ui_label->setToolTip( unit.name );

	layout->addWidget(ui_numinput);

	if(prefixAllowed == false)
		ui_prefixes = new PrefixNone;
	else {
	//TODO: c'est au prefixwidget de formater??
	//TODO: factory pattern?
		switch(Settings::getInstance().prefixPolicy()) {
			case Settings::P_AllPrefixes:
				ui_prefixes = new PrefixAll;
				break;
			case Settings::P_OnlyPow3:
				ui_prefixes = new PrefixPow3;
				break;
			case Settings::P_NoPrefixes:
				ui_prefixes = new PrefixNone;
				break;
		}
		ui_prefixes->setFixedWidth(50);
		layout->addWidget(ui_prefixes);
	}

	layout->addWidget(ui_label);

	connect(ui_numinput, SIGNAL(valueChanged(double)),     this, SIGNAL(valueChanged(double)));
	connect(ui_prefixes, SIGNAL(currentIndexChanged(int)), this, SLOT  (prefixChanged()));
	connect(&Settings::getInstance(), &Settings::symbolTypeChanged, [&](Settings::SymbolType type) {
		ui_label->setText(unit.symbols[type]);
	});

	setLayout(layout);
}

void UnitWidget::setValue(double value) {
	int exponent = 0;
	bool isPositive = value >= 0;
	value = qAbs(value);
	ui_prefixes->formatNumber( value, exponent );

	ui_numinput->setValue( isPositive ? value : -value );
	ui_prefixes->setCurrentIndex(ui_prefixes->exponentToIndex(exponent));
}

double UnitWidget::value() const {
	return ui_numinput->value() * ui_prefixes->indexToExponent(ui_prefixes->currentIndex());
}

void UnitWidget::prefixChanged() {
	emit valueChanged(value());
}
