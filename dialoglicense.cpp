#include "dialoglicense.h"
#include <QtCore/QCoreApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include <QtGui/QIcon>
#include <QtCore/QFile>
#include "compilation_infos.h"

DialogLicense::DialogLicense(QWidget *parent) :
	QDialog(parent)
{
	QVBoxLayout      *ui_vlayout      = new QVBoxLayout;
	QLabel           *ui_license_text = new QLabel;
	QDialogButtonBox *ui_btnbox       = new QDialogButtonBox(QDialogButtonBox::Close, Qt::Horizontal);

	setWindowIcon(QIcon(":/icon/about"));
	setWindowTitle(tr("License"));

#ifdef OS_MOBILE
	setWindowState(windowState() | Qt::WindowMaximized);
#endif

	//License
	QFile license(":/texts/license");
	license.open(QIODevice::ReadOnly);
	ui_license_text->setText(license.readAll());
	license.close();
	ui_license_text->setWordWrap(true);
	//TODO: add in a ScrollBar (Android)

	//Dialog
	ui_vlayout->addWidget( ui_license_text );
#ifndef OS_MOBILE
	ui_vlayout->addWidget( ui_btnbox );
#endif

	setLayout(ui_vlayout);

	connect(ui_btnbox, &QDialogButtonBox::rejected, this, &DialogLicense::accept);

	resize(sizeHint()); //Center the dialog inside its parent
}
