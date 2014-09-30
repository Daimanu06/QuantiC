#include "dialogsettings.h"
#include "browsefileswidget.h"
#include "settings.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include "compilation_infos.h"

/***** Tab Data *****/
DialogTabData::DialogTabData(Settings &settings, QWidget *parent) :
	QWidget(parent),
	ui_data_directory(new BrowseFilesWidget(settings.dataDirectory(),  this)),
	ui_symbol_type   (new QComboBox),
	ui_prefix_policy (new QComboBox)
{
	QFormLayout *ui_layout = new QFormLayout;

	ui_symbol_type->addItems( {"ASCII", "Unicode"} );
	ui_symbol_type->setCurrentIndex(settings.symbolType());

	ui_prefix_policy->addItems( {tr("Full (with c, d, da and h)"), tr("Only power of 3"), tr("Off")} );
	ui_prefix_policy->setCurrentIndex(settings.prefixPolicy());
	//ui_prefix_policy->setDisabled(true);
	ui_prefix_policy->setToolTip("Not implemented yet.");

	ui_layout->addRow(tr("Data location"),  ui_data_directory);
	ui_layout->addRow(tr("Symbols type"),   ui_symbol_type);
	ui_layout->addRow(tr("Prefix policy"),  ui_prefix_policy);

	setLayout(ui_layout);

	connect(ui_data_directory, &BrowseFilesWidget::locationChanged,
			&settings,         &Settings::setDataDirectory
	);
	connect(ui_symbol_type, static_cast<void (QComboBox::*)(int)> (&QComboBox::currentIndexChanged),
			&settings,      &Settings::setSymbolType
	);
	connect(ui_prefix_policy, static_cast<void (QComboBox::*)(int)> (&QComboBox::currentIndexChanged),
			&settings,        &Settings::setPrefixPolicy
	);
}

/***** Tab Home *****/
DialogTabHome::DialogTabHome(Settings &settings, QWidget *parent) :
	QWidget(parent),
	ui_presentation(new QComboBox)
{
	QFormLayout *ui_layout = new QFormLayout;

	ui_presentation->addItems( {tr("Grid"), tr("List")} );
	ui_presentation->setCurrentIndex(settings.homeLayout());

	ui_layout->addRow(tr("Home layout"), ui_presentation);

	setLayout(ui_layout);

	connect(ui_presentation,
			static_cast<void (QComboBox::*)(int)>( &QComboBox::currentIndexChanged ),
			&settings, &Settings::setHomeLayout
	);

}

/***** Tab Window *****/
DialogTabWindow::DialogTabWindow(Settings& settings, QWidget *parent) :
	QWidget(parent),
	ui_save_geo  (new QCheckBox   (tr("Save window geometry"))),
	ui_reset_geo (new QPushButton (tr("Reset window")))
{
	QVBoxLayout *ui_layout = new QVBoxLayout;

	ui_save_geo->setToolTip(tr("Keep the same window position and geometry at the next session."));

	ui_layout->addWidget(ui_save_geo);
	ui_layout->addWidget(ui_reset_geo);
	ui_layout->addSpacing(100); //space added at the bottom of the layout so it doesn't expand vertically
	setLayout(ui_layout);

	ui_save_geo->setChecked( settings.isWindowGeometrySaved() );
	connect( ui_reset_geo, &QPushButton::clicked, this, &DialogTabWindow::resetMainWindow);
	connect( ui_save_geo,  &QCheckBox::clicked,   &settings, &Settings::setWindowGeometrySaved);
}

/***** Dialog Settings *****/
DialogSettings::DialogSettings(Settings& settings, QWidget *parent) :
	QDialog(parent),
	ui_tab_widget(new QTabWidget),
	ui_home_tab  (new DialogTabHome   (settings)),
	ui_data_tab  (new DialogTabData   (settings)),
	ui_win_tab   (new DialogTabWindow (settings)),
	ui_btn_box   (new QDialogButtonBox( QDialogButtonBox::Help | QDialogButtonBox::Close, Qt::Horizontal ))
{
	QVBoxLayout *ui_layout = new QVBoxLayout;

	setWindowIcon(QIcon(":/icon/settings"));
	setWindowTitle(tr("Settings"));

#ifdef OS_MOBILE
	setWindowState(windowState() | Qt::WindowMaximized);
#endif

	ui_layout->addWidget(ui_tab_widget);
	ui_tab_widget->addTab(ui_data_tab, tr("Data"));
	ui_tab_widget->addTab(ui_home_tab, tr("Home"));
#ifndef OS_MOBILE
	ui_tab_widget->addTab(ui_win_tab,  tr("Window"));
#endif

	ui_layout->addWidget(ui_btn_box);
	setLayout(ui_layout);

	connect(ui_win_tab,  &DialogTabWindow::resetMainWindow,   this, &DialogSettings::resetMainWindow);

#ifndef OS_MOBILE
	connect(ui_btn_box,  &QDialogButtonBox::rejected,         this, &DialogSettings::close);
	//connect(ui_btn_box, &QDialogButtonBox::helpRequested,  [](){;});

	ui_btn_box->button(QDialogButtonBox::Help)->setDisabled(true);
	ui_btn_box->button(QDialogButtonBox::Help)->setToolTip("Not implemented yet.");
#endif

	resize(sizeHint()); //Center the dialog inside its parent
}
