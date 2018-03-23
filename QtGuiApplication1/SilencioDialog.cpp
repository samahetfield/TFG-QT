#include "SilencioDialog.h"

SilencioDialog::SilencioDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SilencioDialog::~SilencioDialog()
{
}


void SilencioDialog::on_pushButton_clicked() {
	longitud = ui.spinBox->value();

	close();
}


int SilencioDialog::getLongitud() {
	return longitud;
}
