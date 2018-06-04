#define _CRT_SECURE_NO_DEPRECATE

#include "Almacenar.h"
#include "QFileDialog.h"
#include <string>

using namespace std;

Almacenar::Almacenar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QString filename = QFileDialog::getSaveFileName(this, "Save file");
	ruta = filename.toUtf8().constData();
	ui.lineEdit->setText(filename);
}

Almacenar::~Almacenar()
{
}


//Método con el que indicaremos que el archivo se guarda y cerramos el cuadro de diálogo
void Almacenar::on_pushButton_clicked() {
	guardado = true;
	close();
}

string Almacenar::getPath() {
	return ruta;
}