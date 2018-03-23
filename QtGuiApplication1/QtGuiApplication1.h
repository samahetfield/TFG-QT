#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include "NotaDialog.h"
#include "TremoloDialog.h"
#include "SilencioDialog.h"
#include "CalderonDialog.h"
#include "midi.cpp"

using namespace std;


class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);

private:
	string frase;
	int numero_compases;
	int boton_pulsado;
	Ui::QtGuiApplication1Class ui;
	NotaDialog *nota;
	TremoloDialog *tremolo;
	SilencioDialog *silencio;
	CalderonDialog *calderon;

	public slots:
	void on_pushButton_clicked();
	void on_button_nota_clicked();
	void on_button_tremolo_clicked();
	void on_button_silencio_clicked();
	void on_button_calderon_clicked();
	void on_nueva_voz_clicked();
	void on_play_clicked();
};