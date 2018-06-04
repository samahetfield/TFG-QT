#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include "NotaDialog.h"

NotaDialog::NotaDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

NotaDialog::~NotaDialog()
{
}

// Al pulsar el botón almacenaremos los valores introducidos por el usuario
void NotaDialog::on_pushButton_clicked(){
	
	intensidad = ui.spinBox->value();
	nodo = ui.spinBox_2->value();

	close();
}


int NotaDialog::getIntensidad() {
	return intensidad;
}

int NotaDialog::getNodo() {
	return nodo;
}