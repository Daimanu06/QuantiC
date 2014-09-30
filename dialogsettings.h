#ifndef DIALOGPARAM_H
#define DIALOGPARAM_H

#include <QtWidgets/QDialog>

class Settings;
class QTabWidget;
class BrowseFilesWidget;
class QCheckBox;
class QPushButton;
class QComboBox;
class QDialogButtonBox;

/**
 * @class DialogTabData
 * @ingroup GUI
 * @brief Data tab of the Settings dialog window.
 *
 * @warning Should not be directly used.
 */
class DialogTabData : public QWidget {
	Q_OBJECT

	public:
		explicit DialogTabData(Settings& settings, QWidget *parent = nullptr);

	private:
		BrowseFilesWidget *ui_data_directory;
		QComboBox         *ui_symbol_type;
		QComboBox         *ui_prefix_policy;

};

/**
 * @class DialogTabHome
 * @ingroup GUI
 * @brief Home tab of the Settings dialog window.
 *
 * @warning Should not be directly used.
 */
class DialogTabHome : public QWidget {
	Q_OBJECT

	public:
		explicit DialogTabHome(Settings& settings, QWidget *parent = nullptr);

	private:
		QComboBox *ui_presentation;

};

/**
 * @class DialogTabWindow
 * @ingroup GUI
 * @brief Window tab of the Settings dialog window.
 *
 * @warning Should not be directly used.
 */
class DialogTabWindow : public QWidget {
	Q_OBJECT

	public:
		explicit DialogTabWindow(Settings& settings, QWidget *parent = nullptr);

	private:
		QCheckBox   *ui_save_geo;
		QPushButton *ui_reset_geo;

	signals:
		void resetMainWindow();

};

/**
 * @class DialogSettings
 * @ingroup GUI
 * @brief Tab widget made of three tabs (Data, Home and Window), and a button box ("Close" and "Help").
 *
 * @see DialogTabData
 * @see DialogTabHome
 * @see DialogTabWindow
 */
class DialogSettings : public QDialog {
	Q_OBJECT

	public:
		explicit DialogSettings(Settings& settings, QWidget *parent = nullptr);

	signals:
		void updateData();
		void reloadData();
		void resetMainWindow();

	private:
		QTabWidget       *ui_tab_widget;
		DialogTabHome    *ui_home_tab;
		DialogTabData    *ui_data_tab;
		DialogTabWindow  *ui_win_tab;
		QDialogButtonBox *ui_btn_box;

};

#endif // DIALOGPARAM_H
