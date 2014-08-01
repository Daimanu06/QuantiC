#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include <QtWidgets/QLayout>

class TileLayout : public QLayout {
	public:
		TileLayout(const QSize &tileSize, QWidget *parent = nullptr);
		~TileLayout();

		void addItem(QLayoutItem *item);
		int count() const;
		QLayoutItem *itemAt(int exponent) const;
		QLayoutItem *takeAt(int exponent);

		Qt::Orientations expandingDirections() const;
		bool hasHeightForWidth() const;
		int  heightForWidth(int width) const;

		QSize sizeHint() const;
		void setGeometry(const QRect &rect);

	private:
		void doLayout() const;

	private:
		QList<QLayoutItem *> itemList;
		const QSize     m_tile_size;
		uint tileperline;
};

#endif // FLOWLAYOUT_H
