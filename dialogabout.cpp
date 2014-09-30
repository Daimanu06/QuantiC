#include "dialogabout.h"
#include <QtCore/QCoreApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include <QtGui/QIcon>
#include <QtCore/QDate>
#include <QtCore/QFile>
#include "compilation_infos.h"

DialogAbout::DialogAbout(QWidget *parent) :
	QDialog(parent)
{
	QVBoxLayout      *ui_vlayout    = new QVBoxLayout;
	QLabel           *ui_about_text = new QLabel;
	QDialogButtonBox *ui_btnbox     = new QDialogButtonBox(QDialogButtonBox::Close, Qt::Horizontal);

	setWindowIcon(QIcon(":/icon/about"));
	setWindowTitle(tr("About"));

#ifdef OS_MOBILE
	setWindowState(windowState() | Qt::WindowMaximized);
#endif

	//Icon and presentation text
	ui_about_text->setText(
		tr(
			"<html><body>"
			"<p><span style=\"font-size: 20px; font-weight: bold;\">%1</span></p>"
			"<p><span style=\"font-size: 14px;\">%1 is a light, flexible and cross platform physical quantity converter.</span></p>"
			"<p><span style=\"font-size: 14px;\">Copyright &#169; %3 Emmanuel Di Clemente</span></p>"
			"<p><span style=\"font-size: 12px;\">Build %2 (%6 %7) %4 %5</span></p>"
			"</body></html>"
		)
		.arg(QCoreApplication::applicationName())
		.arg(QCoreApplication::applicationVersion())
		.arg(QDate::currentDate().year())
		.arg(os_name())
		.arg(proc_name())
		.arg(__DATE__)
		.arg(__TIME__)
	);
	ui_about_text->setWordWrap(true);
	//TODO: add in a ScrollBar (Android)

	//Dialog
	ui_vlayout->addWidget(ui_about_text);
#ifndef OS_MOBILE
	ui_vlayout->addWidget( ui_btnbox );
#endif

	setLayout(ui_vlayout);

	connect(ui_btnbox, &QDialogButtonBox::rejected, this, &DialogAbout::accept);

	resize(sizeHint()); //Center the dialog inside its parent
}
