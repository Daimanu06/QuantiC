#include "tilelayout.h"
#include <QtWidgets/QWidget>

TileLayout::TileLayout(const QSize& tileSize, QWidget *parent) :
	QLayout(parent),
	m_tile_size (tileSize)
{}
TileLayout::~TileLayout() {
	QLayoutItem *item;
	while ((item = takeAt(0)))
		delete item;
}

void TileLayout::addItem(QLayoutItem *item) {
	itemList.append(item);
}
int TileLayout::count() const {
	return itemList.size();
}
QLayoutItem *TileLayout::itemAt(int index) const {
	return itemList.value(index);
}
QLayoutItem *TileLayout::takeAt(int index) {
	return index >= 0 && index < itemList.size() ? itemList.takeAt(index) : 0;
}

Qt::Orientations TileLayout::expandingDirections() const {
	return Qt::Horizontal | Qt::Vertical;
}
bool TileLayout::hasHeightForWidth() const {
	return true;
}
int  TileLayout::heightForWidth(int width) const {
	Q_UNUSED(width);
	return sizeHint().height();
}

QSize TileLayout::sizeHint() const {
	// Ideal size, ie. current width + enough height to display vertically all widgets.

	if(tileperline == 0)
		return QSize(0, 0);

	uint lines = itemList.count() / tileperline + (int)(itemList.count() % tileperline != 0);
	return QSize(  geometry().width(),  lines*(m_tile_size.width() + 2*spacing())  );
//TODO: according to Valgrind, there is a memory error in this function
}

void TileLayout::setGeometry(const QRect &rect) {
	QLayout::setGeometry(rect);

	const QMargins &margins = contentsMargins();
	//Compute how many widgets can be placed in one line
	//Available width (width - margins) ÷ Full tile width (tile_width + spacings)
	tileperline =  (rect.width() - margins.left() - margins.right()) / (m_tile_size.width() + 2*spacing());

	if(tileperline == 0) return;

	uint remaining_space = geometry().width() - margins.left() - margins.right() - tileperline*(m_tile_size.width() + 2*spacing());
	uint column = 0, line = 0;

	for(int index = 0; index < itemList.count(); index++) {
		column = index % tileperline;
		line   = index / tileperline;
		itemList.at(index)->setGeometry(
			QRect(
				column*(m_tile_size.width()  + 2*spacing()) + margins.left() + spacing() + remaining_space/2,
				line  *(m_tile_size.height() + 2*spacing()) + margins.top()  + spacing(),
				m_tile_size.width(),
				m_tile_size.height()
			)
		);
	}
}
