/**
 * @mainpage
 * @brief QuantiC is a light physical quantity converter.
 * This project is written with C++ and Qt.
 * @author Emmanuel "Daïmanu" DI CLEMENTE
 * @copyright GNU Public License
 */

#include "mainwindow.h"
#include "dialogsettings.h"
#include "dialogabout.h"
#include "dialoglicense.h"
#include "settings.h"
#include <QtWidgets/QApplication>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>
#include <QtCore/QUrl>
#include <QtGui/QDesktopServices>  //QDesktopServices::openUrl();

int main(int argc, char** argv) {
	//QT_REQUIRE_VERSION(argc, argv, "5.1.0"); //requires <QMessageBox> instead of <QtGlobal> ??

	QApplication app(argc, argv);

/***** settings *****/
	QApplication::setOrganizationName  ("Daimanu");
	QApplication::setOrganizationDomain("http://127.0.0.1"); //TODO: update website url
	QApplication::setApplicationName   ("QuantiC");
	QApplication::setApplicationVersion("0.6.0");
	QApplication::setWindowIcon        (QIcon(":/icon/app128"));

	Settings& settings = Settings::getInstance();

/***** translatie my strings and the application one *****/
	QTranslator qtTranslator;
	qtTranslator.load ( QLocale::system(), "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath) );
	app.installTranslator(&qtTranslator);

	QTranslator appTranslator;
	appTranslator.load( QLocale::system() , QApplication::applicationName(), ".", QApplication::applicationDirPath() );
	app.installTranslator(&appTranslator);

/***** create main window and dialogs *****/
	MainWindow     mainwindow(settings);
	DialogSettings dialogSettings(settings, &mainwindow);
	DialogAbout    dialogabout(&mainwindow);
	DialogLicense  dialogLicense(&mainwindow);

	QObject::connect(&mainwindow,     &MainWindow::showDialogSettings,  &dialogSettings, &DialogSettings::exec);
	QObject::connect(&mainwindow,     &MainWindow::showDialogAbout,     &dialogabout,    &DialogAbout::exec);
	QObject::connect(&mainwindow,     &MainWindow::showDialogLicense,   &dialogLicense,  &DialogLicense::exec);
	QObject::connect(&settings,       &Settings::dataLocationChanged,   &mainwindow,     &MainWindow::reloadData);
	QObject::connect(&settings,       &Settings::iconsLocationChanged,  &mainwindow,     &MainWindow::reloadData);
	//TODO: when iconLocation or prefixPolicy changes, reload all?
	QObject::connect(&settings,       &Settings::prefixPolicyChanged,   &mainwindow,     &MainWindow::reloadData);
	QObject::connect(&dialogSettings, &DialogSettings::resetMainWindow, &mainwindow,     &MainWindow::resetWindow);
	QObject::connect(&mainwindow,     &MainWindow::visitWebsite,
				[](){ QDesktopServices::openUrl(  QUrl(  QApplication::organizationDomain()+"/QuantiC/"  )  ); }
	);

	mainwindow.show();

	return app.exec();
}
