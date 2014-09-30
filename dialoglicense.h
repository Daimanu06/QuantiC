#ifndef DIALOGLICENSE_H
#define DIALOGLICENSE_H

#include <QtWidgets/QDialog>

/**
 * @class DialogLicense
 * @ingroup GUI
 * @brief License dialog window
 *
 * Displays the license of the application:
 */
class DialogLicense : public QDialog {
	Q_OBJECT

	public:
		explicit DialogLicense(QWidget *parent = nullptr);

};

#endif // DIALOGLICENSE_H
