#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include "CalderonDialog.h"

CalderonDialog::CalderonDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

}

CalderonDialog::~CalderonDialog()
{
}


// Al pulsar el botón almacenaremos los valores introducidos por el usuario
void CalderonDialog::on_pushButton_clicked() {
	fragmento = ui.spinBox->value();
	longitud = ui.spinBox_2->value();

	close();
}


int CalderonDialog::getFragmento() {
	return fragmento;
}

int CalderonDialog::getLongitud() {
	return longitud;
}

void CalderonDialog::setMax(int maxi) {
	ui.spinBox->setMaximum(maxi);
}
