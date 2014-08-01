#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtWidgets/QDialog>

/**
   @class DialogAbout
 * @ingroup GUI
 * @brief About dialog window
 *
 * Displays a short presentation text and the application icon.
 */
class DialogAbout : public QDialog {
	Q_OBJECT

	public:
		explicit DialogAbout(QWidget *parent = nullptr);

};

#endif // ABOUTDIALOG_H
