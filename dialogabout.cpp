#include "dialogabout.h"
#include <QtCore/QCoreApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include <QtGui/QIcon>
#include <QtCore/QDate>

DialogAbout::DialogAbout(QWidget *parent) :
	QDialog(parent)
{
	QVBoxLayout      *ui_vlayout = new QVBoxLayout;
	QHBoxLayout      *ui_hlayout = new QHBoxLayout;
	QLabel           *ui_icon    = new QLabel;
	QLabel           *ui_text    = new QLabel;
	QDialogButtonBox *ui_btnbox  = new QDialogButtonBox(QDialogButtonBox::Close, Qt::Horizontal);

	setWindowIcon(QIcon(":/icon/about"));
	setWindowTitle(tr("About"));

	//Icon and presentation text
	ui_icon->setPixmap( QPixmap(":/icon/app") );
	ui_text->setText(
		tr("<p>%1 v%2</p><p>%1 is a light, flexible and cross platform physical quantity converter.</p><p>Copyright &#169; %3 Emmanuel Di Clemente</p>")
		.arg(QCoreApplication::applicationName())
		.arg(QCoreApplication::applicationVersion())
		.arg(QDate::currentDate().year())
	);

	connect(ui_btnbox, &QDialogButtonBox::rejected, this, &DialogAbout::accept);

	ui_hlayout->addWidget( ui_icon );
	ui_hlayout->addWidget( ui_text );
	ui_vlayout->addLayout( ui_hlayout );
	ui_vlayout->addWidget( ui_btnbox );

	setLayout(ui_vlayout);

	resize(sizeHint()); //Center the dialog inside its parent
}
