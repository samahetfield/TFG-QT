#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include "SilencioDialog.h"

SilencioDialog::SilencioDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SilencioDialog::~SilencioDialog()
{
}

// Al pulsar el botón almacenaremos los valores introducidos por el usuario
void SilencioDialog::on_pushButton_clicked() {
	longitud = ui.spinBox->value();

	close();
}


int SilencioDialog::getLongitud() {
	return longitud;
}
