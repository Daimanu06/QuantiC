#include "mainwindow.h"
#include "centralwidget.h"
#include "settings.h"
#include <QtWidgets/QApplication> //qApp::aboutQt(), QApplication::applicationName()
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QLabel>
#include <QtCore/QDir>
#include "datamanager.h"

MainWindow::MainWindow(Settings& set, QWidget *parent) :
	QMainWindow(parent),
	settings(set)
{
	setGeometry(settings.windowGeometry());
	settings.isWindowMaximized() ? showMaximized() : showNormal();

	setWindowIcon(QIcon(":/icon/app"));
	setWindowTitle(QApplication::applicationName());

	createMenuBar();
	createStatusBar();

	setCentralWidget( new CentralWidget(this) );

	reloadData(); //Load quantities for the first time
}

MainWindow::~MainWindow() {
	settings.setWindowMaximized(isMaximized());
	settings.setWindowGeometry(geometry());
}

/******************** MAIN WIDGETS ********************/
void MainWindow::createMenuBar() {
	QMenuBar *menuBar  = new QMenuBar(this);
	QMenu    *menuApp  = new QMenu(tr("&Application"), menuBar);
	QMenu    *menuHelp = new QMenu(tr("&Help"), menuBar);

	//QKeySequence::Preferences is only defined for Gnome
	menuApp->addAction(QIcon(":/icon/settings"), tr("Settings"), this, SIGNAL(showDialogSettings()), QKeySequence(Qt::CTRL + Qt::Key_P));
	menuApp->addSeparator();
	menuApp->addAction(QIcon(":/icon/quit"),     tr("Quit"),     this, SLOT(close()),                QKeySequence(QKeySequence::Quit));

	menuHelp->addAction(QIcon(":/icon/about"),   tr("About"),    this, SIGNAL(showDialogAbout()),    QKeySequence(Qt::Key_F2));
	menuHelp->addAction(QIcon(":/icon/about"),   tr("About Qt"), qApp, SLOT(aboutQt()),              QKeySequence(Qt::Key_F3));
	menuHelp->addAction(QIcon(":/icon/about"),   tr("Website"),  this, SIGNAL(visitWebsite()),       QKeySequence(Qt::Key_F4));
	menuHelp->addAction(QIcon(":/icon/about"),   tr("Licenses"), this, SIGNAL(showDialogLicenses()), QKeySequence(Qt::Key_F5));

	menuBar->addMenu(menuApp);
	menuBar->addMenu(menuHelp);

	setMenuBar(menuBar);
}
void MainWindow::createStatusBar() {
	QStatusBar *statusBar = new QStatusBar(this);
	statusBar->addPermanentWidget(new QLabel(QLocale::system().bcp47Name()));
	setStatusBar(statusBar);
}

/********************** EVENTS **********************/
void MainWindow::resetWindow() {
	showNormal();
	setGeometry( defaultGeometry() );
}

void MainWindow::reloadData() {
	DataManager &manager = DataManager::getInstance();
	manager.clear();
	manager.loadQuantities(
			QDir( settings.dataLocation(),  QString("*.xml"), QDir::Name, QDir::Files ),
			QDir( settings.iconsLocation(), QString("*.png"), QDir::Name, QDir::Files )
	);
	dynamic_cast<CentralWidget*>( centralWidget() )->reloadData();
}

/********************** OTHER **********************/
//Static method
const QRect MainWindow::defaultGeometry() {
	return QRect(470, 200, 500, 500);
}
