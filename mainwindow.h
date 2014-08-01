#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class Settings;

/**
 * @class MainWindow
 * @ingroup GUI
 */
class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		explicit MainWindow(Settings &set, QWidget *parent = nullptr);
		~MainWindow();

	private:
		void createMenuBar();
		void createStatusBar();

	public slots:
		/**
		 * @fn reloadData
		 * @brief Reload all the datas from a new location.
		 *
		 * The pages (QuantityWidget) will be deleted and recreated if new datas ara found.
		 */

		void reloadData();
		/**
		 * @fn resetWindow
		 * @brief Reset the main window position and geometry.
		 */
		void resetWindow();

	private: //static private methods
		static const QRect defaultGeometry();

	signals:
		void showDialogSettings();
		void showDialogAbout();
		void showDialogLicenses();
		void visitWebsite();

	private:
		Settings& settings;

};

#endif // MAINWINDOW_H
