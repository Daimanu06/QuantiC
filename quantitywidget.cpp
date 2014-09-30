#include "quantitywidget.h"
#include "unitwidget.h"
#include "data.h"
#include "prefixwidget.h"
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QSignalMapper>

QuantityWidget::QuantityWidget(Quantity& quantity, QWidget *parent) :
	QWidget(parent),
	quantity(quantity),
	mapper(new QSignalMapper(this))
{
	QVBoxLayout *layout = new QVBoxLayout;

	for(int i = 0; i < quantity.count(); i++) {
		UnitWidget *unit_widget = new UnitWidget(quantity.at(i), quantity.prefixAllowed, this);
		units.push_back(unit_widget);

		mapper->setMapping(unit_widget, i);
		connect(unit_widget, SIGNAL(valueChanged(double)), mapper, SLOT(map()));
		layout->addWidget(unit_widget);

	}
	layout->addItem( new QSpacerItem(width(), 0, QSizePolicy::Minimum, QSizePolicy::Expanding) );

	connect(mapper, SIGNAL(mapped(int)), this, SLOT(aValueHasChanged(int)));

	setLayout(layout);
}

void QuantityWidget::aValueHasChanged(int index) {
	for(int i = 0; i < units.size(); i++) {
		if(i == index) continue; //Skip the spin box that triggered the signal

		UnitWidget* unit_widget = units.at(i);
		unit_widget->blockSignals(true); //Block spinboxes signal emission, to prevent multiplication of signals…
		unit_widget->setValue(   quantity[i].fromBaseUnit(  quantity[index].toLegalUnit( units.at(index)->value() )  )   );
		unit_widget->blockSignals(false); //…then, make signals effective again
	}
}
