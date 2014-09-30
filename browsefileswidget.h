#ifndef BROWSEFILESWIDGET_H
#define BROWSEFILESWIDGET_H

#include <QtWidgets/QWidget>

class QLineEdit;
class QPushButton;

/**
 * @class BrowseFilesWidget
 * @ingroup GUI
 * @brief LineEdit and PushButton horizontaly aligned.
 *
 * The user inputs a directory where the software can search files.
 * Used in the settings dialog window.
 */
class BrowseFilesWidget : public QWidget {
	Q_OBJECT

	public:
		explicit BrowseFilesWidget(const QString& default_location, QWidget *parent = nullptr);
		
	signals:
		void locationChanged(const QString&);

	public slots:
		void showFileDialog();

	public:
		void setLocation(const QString&);
		QString location();

	private:
		QLineEdit   *ui_line_edit;
		QPushButton *ui_browse;
};

#endif // BROWSEFILESWIDGET_H
