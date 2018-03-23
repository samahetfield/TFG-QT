#include "NotaDialog.h"

NotaDialog::NotaDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

NotaDialog::~NotaDialog()
{
}


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