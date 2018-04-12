#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include "TremoloDialog.h"
#include <QtCore\qstring.h>
#include <QtWidgets/QMessageBox>
#include <string>
#include <iostream>

using namespace std;

TremoloDialog::TremoloDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QStringList list = (QStringList() << "Tremolo Intensidad" << "Tremolo Velocidad" << "Tremolo Normal");
	ui.comboBox->addItems(list);
}

TremoloDialog::~TremoloDialog()
{
}


void TremoloDialog::on_comboBox_currentIndexChanged() {
	string tipo = (ui.comboBox->currentText()).toUtf8().constData();

	if (tipo == "Tremolo Intensidad") {
		ui.spinBox_3->setEnabled(true);
		ui.spinBox_4->setEnabled(true);
		ui.spinBox_5->setEnabled(true);
	}
	else if (tipo == "Tremolo Velocidad") {
		ui.spinBox_3->setEnabled(true);
		ui.spinBox_5->setEnabled(false);

	}
	else {
		ui.spinBox_3->setEnabled(false);
		ui.spinBox_5->setEnabled(false);
	}


}

void TremoloDialog::on_pushButton_clicked() {
	tipo_tremolo = (ui.comboBox->currentText()).toUtf8().constData();
	longitud = ui.spinBox->value();
	velocidad_ini = ui.spinBox_2->value();
	velocidad_fin = ui.spinBox_3->value();
	intensidad_ini = ui.spinBox_4->value();
	intensidad_fin = ui.spinBox_5->value();

	close();

}

int TremoloDialog::getLongitud() {
	return longitud;
}

int TremoloDialog::getIntensidadIni() {
	return intensidad_ini;
}

int TremoloDialog::getIntensidadFin() {
	return intensidad_fin;
}

int TremoloDialog::getVelocidadIni() {
	return velocidad_ini;
}

int TremoloDialog::getVelocidadFin() {
	return velocidad_fin;
}

string TremoloDialog::getTipoTremolo() {
	return tipo_tremolo;
}