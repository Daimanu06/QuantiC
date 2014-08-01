#include "banner.h"
#include "datamanager.h"
#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

/***** BannerButton ****/
BannerButton::BannerButton(QWidget *parent) :
	QAbstractButton(parent)
{
	setFixedHeight(80);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
void BannerButton::paintEvent(QPaintEvent *e) {
	static QFont font;
	font.setPointSize(30);

	QPainter p(this);
	p.setFont (font);
	p.setPen  (Qt::black);
	p.setBrush(Qt::black);
	p.drawText(rect(), Qt::AlignVCenter | Qt::AlignLeft, text());
	e->accept();
}

/***** BannerArrow ****/
BannerArrow::BannerArrow(const QPixmap& pix , const QPixmap& pix_press, QWidget *parent) :
	QAbstractButton(parent),
	m_pix_released(pix),
	m_pix_pressed (pix_press),
	m_pressed     (false)
{
	setFixedSize(50, 80);
}
void BannerArrow::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	if(!m_pix_released.isNull() && !m_pix_pressed.isNull())
		p.drawPixmap(rect(), m_pressed ? m_pix_pressed : m_pix_released);
	e->accept();
}
void BannerArrow::mousePressEvent(QMouseEvent *e) {
	QAbstractButton::mousePressEvent(e);
	m_pressed = true;
	update();
}
void BannerArrow::mouseReleaseEvent(QMouseEvent *e) {
	QAbstractButton::mouseReleaseEvent(e);
	m_pressed = false;
	update();
}

/***** Banner ****/
Banner::Banner(QWidget *parent) :
	QWidget(parent),
	datamanager(DataManager::getInstance()),
	m_index(0),
	m_arrow_left (new BannerArrow(QPixmap(":/arrow/left"),  QPixmap(":/arrow/left_press"),  this)),
	m_arrow_right(new BannerArrow(QPixmap(":/arrow/right"), QPixmap(":/arrow/right_press"), this)),
	m_title      (new BannerButton(this)),
	m_image      (new QLabel(this))
{
	QHBoxLayout *layout = new QHBoxLayout(this);

	m_image->setFixedSize(80, 80);

	layout->setSpacing(2);
	layout->setContentsMargins(0, 0, 0, 0);

	layout->addWidget(m_arrow_left);
	layout->addWidget(m_image);
	layout->addWidget(m_title);
	layout->addWidget(m_arrow_right);

	setLayout(layout);

	connect(m_arrow_left,  &BannerArrow::clicked,  this, &Banner::decreaseCurrentIndex);
	connect(m_arrow_right, &BannerArrow::clicked,  this, &Banner::increaseCurrentIndex);
	connect(m_title,       &BannerButton::clicked, this, &Banner::returnHome);
}

void Banner::setCurrentIndex(int index) {
	auto toSentenceCase = [&](QString str)->QString&{
		str    = str.toLower();
		str[0] = str[0].toUpper();
		return str;
	};

	m_index = index;
	QPixmap pix;
	if(m_index == 0) {
		m_title->setText(tr("Home"));
		pix = QPixmap(":/icon/home");
	} else {
		QString title = datamanager.at(m_index-1).name;
		m_title->setText(toSentenceCase(title));
		pix = datamanager.at(m_index-1).image;
	}
	m_image->setPixmap(pix.scaled(m_image->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	emit currentIndexChanged(m_index);
}
void Banner::decreaseCurrentIndex() {
	setCurrentIndex((m_index > 0) ? m_index-1 : datamanager.count());
}
void Banner::increaseCurrentIndex() {
	setCurrentIndex((m_index + 1) % (datamanager.count()+1));
}
void Banner::returnHome() {
	setCurrentIndex(0);
}
int Banner::currentIndex() const {
	return m_index;
}

void Banner::reloadData() {
	returnHome(); //! @note when datamanager is emptied, redirect to home to avoid pointing a potential empty area
	QWidget::update();
}
