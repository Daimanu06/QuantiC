#include "homewidget.h"
#include <QtCore/QSignalMapper>

HomeWidget::HomeWidget(QWidget *parent) :
	QWidget(parent),
	m_mapper(new QSignalMapper(this))
{}
