#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication1 w; // Llamamos a la clase de la interfaz ejecutable

	w.show(); // Mostramos la ventana de la interfaz

	
	return a.exec();
}
