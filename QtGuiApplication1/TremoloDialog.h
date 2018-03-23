#pragma once

#include <QDialog>
#include <string>
#include "ui_TremoloDialog.h"

using namespace std;

class TremoloDialog : public QDialog
{
	Q_OBJECT

public:
	TremoloDialog(QWidget *parent = Q_NULLPTR);
	~TremoloDialog();
	int getLongitud();
	int getVelocidadIni();
	int getVelocidadFin();
	int getIntensidadIni();
	int getIntensidadFin();
	string getTipoTremolo();

public slots:
	void on_pushButton_clicked();
	void on_comboBox_currentIndexChanged();




private:
	Ui::TremoloDialog ui;
	string tipo_tremolo;
	int longitud;
	int intensidad_ini;
	int intensidad_fin;
	int velocidad_ini;
	int velocidad_fin;
};
