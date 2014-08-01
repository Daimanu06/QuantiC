#include "browsefileswidget.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>

BrowseFilesWidget::BrowseFilesWidget(const QString& default_location, QWidget *parent) :
	QWidget(parent),
	ui_line_edit(new QLineEdit  (default_location)),
	ui_browse   (new QPushButton(tr("Browse", "Browse files")))
{
	QHBoxLayout *ui_layout = new QHBoxLayout;

	ui_line_edit->setReadOnly(true);
	connect(ui_line_edit, &QLineEdit::textChanged, this, &BrowseFilesWidget::locationChanged);
	connect(ui_browse,    &QPushButton::clicked,   this, &BrowseFilesWidget::showFileDialog);

	ui_layout->addWidget(ui_line_edit);
	ui_layout->addWidget(ui_browse);

	setLayout(ui_layout);
}

void BrowseFilesWidget::showFileDialog() {
	const QString& str = QFileDialog::getExistingDirectory(this, tr("Select a directory"), ui_line_edit->text(), QFileDialog::ShowDirsOnly);
	if(!str.isEmpty())
		ui_line_edit->setText(str);
}

void BrowseFilesWidget::setLocation(const QString& s) {
	ui_line_edit->setText(s);
}
QString BrowseFilesWidget::location() {
	return ui_line_edit->text();
}
