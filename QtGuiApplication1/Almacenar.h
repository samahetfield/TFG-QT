#pragma once

#include <QWidget>
#include "ui_Almacenar.h"
#include <string>

using namespace std;

class Almacenar : public QWidget
{
	Q_OBJECT

public:
	Almacenar(QWidget *parent = Q_NULLPTR);
	string getPath();
	~Almacenar();

public slots:
	void on_pushButton_clicked();

private:
	Ui::Almacenar ui;
	string ruta;
	bool guardado;
};
