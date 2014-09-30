#ifndef BANNER_H
#define BANNER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QAbstractButton>

class QPixmap;
class QLabel;
class DataManager;

/**
 * @class BannerButton
 * @ingroup GUI
 * @brief Clickable text button for the Banner.
 *
 * When clicked, the application returns to the home screen.
 * @warning Should not be directly used.
 */
class BannerButton : public QAbstractButton {
	Q_OBJECT

	public:
		explicit BannerButton(QWidget *parent = nullptr);

	protected:
		virtual void paintEvent(QPaintEvent *e);
};

/**
 * @class BannerArrow
 * @ingroup GUI
 * @brief Clickable arrow button for the Banner.
 *
 * When clicked, the application shows another quantity screen.
 * @warning Should not be directly used.
 */
class BannerArrow : public QAbstractButton {
	Q_OBJECT

	public:
		explicit BannerArrow(const QPixmap& pix , const QPixmap& pix_press, QWidget *parent = nullptr);

	protected:
		virtual void paintEvent(QPaintEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);

	private:
		QPixmap m_pix_released;
		QPixmap m_pix_pressed;
		bool    m_pressed;
};

/**
 * @class Banner
 * @ingroup GUI
 * @brief Banner widget displayed in the top of the window.
 *
 * Made of two arrows (left and right), the icon and the title of the current quantity.
 * When the user clicks an arrow, the quantity changes.
 * When the user clicks the title / icon, the software returns to the home page.
 */
class Banner : public QWidget {
	Q_OBJECT

	public:
		explicit Banner(QWidget *parent = nullptr);

	public slots:
		void setCurrentIndex(int index);
		void decreaseCurrentIndex();
		void increaseCurrentIndex();
		void returnHome();

	public:
		void reloadData();

	signals:
		void currentIndexChanged(int index);

	public:
		int currentIndex() const;

	private:
		DataManager&  datamanager;
		int           m_index;
		BannerArrow  *m_arrow_left;
		BannerArrow  *m_arrow_right;
		BannerButton *m_title;
		QLabel       *m_image;
};

#endif // BANNER_H
