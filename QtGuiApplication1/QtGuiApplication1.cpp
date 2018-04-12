#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include "QtGuiApplication1.h"
#include <QtWidgets/QMessageBox>
#include <QtCore\qstring.h>
#include <string>
#include <cstdio>  // For std::fopen, std::fwrite, std::fclose
#include <fstream>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	numero_compases = 0;

	ui.setupUi(this);
	
	QStringList list = (QStringList() << "Bombo" << "Caja" << "Hit-Hat (abierto)" << "Hit-hat (cerrado)");
	ui.comboBox->addItems(list);

	QIcon nota_icon(QPixmap(".\\img\\nota.png"));
	QIcon tremolo_icon(QPixmap(".\\img\\tremolo.png"));
	QIcon silencio_icon(QPixmap(".\\img\\silencio.png"));
	QIcon calderon_icon(QPixmap(".\\img\\calderon.png"));
	QIcon play_icon(QPixmap(".\\img\\play.png"));

	ui.button_nota->setIcon(nota_icon);
	ui.button_tremolo->setIcon(tremolo_icon);
	ui.button_silencio->setIcon(silencio_icon);
	ui.button_calderon->setIcon(calderon_icon);
	ui.play->setIcon(play_icon);
	voces = new string[1];
	tab_voz = new QTableWidget*[1];
	tab_voz[0] = ui.tableWidget;
	voces_size = 1;

}


void QtGuiApplication1::on_button_nota_clicked() {
	nota = new NotaDialog(this);
	nota->show();
	boton_pulsado = 0;
}

void QtGuiApplication1::on_button_tremolo_clicked() {
	tremolo = new TremoloDialog(this);
	tremolo->show();
	boton_pulsado = 1;
}

void QtGuiApplication1::on_button_silencio_clicked() {
	silencio = new SilencioDialog(this);
	silencio->show();
	boton_pulsado = 2;
}

void QtGuiApplication1::on_button_calderon_clicked() {
	calderon = new CalderonDialog(this);
	calderon->setMax(numero_compases);
	calderon->show();
	boton_pulsado = 3;
}

void QtGuiApplication1::on_nueva_voz_clicked() {
	QWidget *nuevo_w = new QWidget();
	QTableWidget *nueva_voz = new QTableWidget(6,0,nuevo_w);
	nueva_voz->setGeometry(10, 10, 850, 230);

	ui.tabWidget->addTab(nuevo_w, QString("Voz %0").arg(ui.tabWidget->count() +1));

	QTableWidget **tab_aux = new QTableWidget*[voces_size+1];

	for (int i = 0; i < voces_size; i++) {
		tab_aux[i] = tab_voz[i];
	}

	tab_aux[voces_size - 1] = nueva_voz;

	delete[] tab_voz;
	tab_voz = tab_aux;

	string *aux = new string[voces_size + 1];

	for (int i = 0; i < voces_size; i++) {
		aux[i] = voces[i];
	}

	delete[] voces;
	voces = aux;
	voces_size++;
}




void QtGuiApplication1::on_pushButton_clicked() {
	string midi_instrumento = "";
	string instrumento;
	int fila = 0;
	frase = "";
	
	switch (boton_pulsado)
	{
	case 0: {
		frase += "Nota-";
		int intensidad = nota->getIntensidad();
		frase += to_string(intensidad) + " ";

		int nodo = nota->getNodo();
		frase += to_string(nodo) + " ";

		instrumento = (ui.comboBox->currentText()).toUtf8().constData();

		if (instrumento == "Caja") {
			midi_instrumento = "38";
		}
		else if (instrumento == "Bombo") {
			midi_instrumento = "35";
		}
		else if (instrumento == "Hit-Hat (abierto)") {
			midi_instrumento = "44";
		}
		else if (instrumento == "Hit-Hat (cerrado)") {
			midi_instrumento = "46";
		}


		frase += midi_instrumento + "\n";

		if (intensidad <= 22) {
			fila = 5;
		}
		else if (intensidad > 22 && intensidad <= 44) {
			fila = 4;
		}
		else if (intensidad > 44 && intensidad <= 66) {
			fila = 3;
		}
		else if (intensidad > 66 && intensidad <= 88) {
			fila = 2;
		}
		else if (intensidad > 88 && intensidad <= 110) {
			fila = 1;
		}
		else if (intensidad >= 110) {
			fila = 0;
		}

		int f_aux = ui.tabWidget->currentIndex();

		string voz_aux = voces[f_aux];
		voz_aux += frase;

		voces[f_aux] = voz_aux;

		QTableWidget *tab_select = tab_voz[f_aux];

		tab_select->insertColumn(tab_select->columnCount());
		//ui.tableWidget->insertColumn(ui.tableWidget->columnCount());
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setIcon(QIcon(".\\img\\nota.png"));
		tab_select->setItem(fila, numero_compases, item);
		//ui.tableWidget->setItem(fila, numero_compases, item);

		break;
	}

	case 1: {
		frase += "Tremolo-";
		string tipo_tremolo = tremolo->getTipoTremolo();

		int longitud = tremolo->getLongitud();

		if (tipo_tremolo == "Tremolo Intensidad") {
			int velocidad_ini = tremolo->getVelocidadIni();
			int velocidad_fin = tremolo->getVelocidadFin();
			int intensidad_ini = tremolo->getIntensidadIni();
			int intensidad_fin = tremolo->getIntensidadFin();

			frase += "Intensidad "+to_string(longitud) + " "+ to_string(velocidad_ini) + " " + to_string(velocidad_fin) + " " + to_string(intensidad_ini) + " " + to_string(intensidad_fin) + " ";
		}
		else if (tipo_tremolo == "Tremolo Velocidad") {
			int velocidad_ini = tremolo->getVelocidadIni();
			int velocidad_fin = tremolo->getVelocidadFin();
			int intensidad_ini = tremolo->getIntensidadIni();
			frase += "Tiempo "+ to_string(longitud) + " "+to_string(velocidad_ini) + " " + to_string(velocidad_fin) + " " + to_string(intensidad_ini) + " ";
		}
		else {
			int velocidad_ini = tremolo->getVelocidadIni();
			int intensidad_ini = tremolo->getIntensidadIni();

			frase += "Normal "+ to_string(longitud) + " "+to_string(velocidad_ini) + " " + to_string(velocidad_ini) + " " + to_string(intensidad_ini) + " " + to_string(intensidad_ini) + " ";
		}


			instrumento = (ui.comboBox->currentText()).toUtf8().constData();

			if (instrumento == "Caja") {
				midi_instrumento = "38";
			}
			else if (instrumento == "Bombo") {
				midi_instrumento = "35";
			}
			else if (instrumento == "Hit-Hat (abierto)") {
				midi_instrumento = "44";
			}
			else if (instrumento == "Hit-Hat (cerrado)") {
				midi_instrumento = "46";
			}

			frase += midi_instrumento + "\n";

			int f_aux = ui.tabWidget->currentIndex();

			string voz_aux = voces[f_aux];
			voz_aux += frase;

			ui.tableWidget->insertColumn(ui.tableWidget->columnCount());
			QTableWidgetItem* item = new QTableWidgetItem;
			item->setIcon(QIcon(".\\img\\tremolo.png"));
			ui.tableWidget->setItem(fila, numero_compases, item);


		break;
	}


	case 2: {

		int longitud;

		for (int i = 0; i < silencio->getLongitud(); i++) {
			frase += "Silencio\n";
		}

		int f_aux = ui.tabWidget->currentIndex();

		string voz_aux = voces[f_aux];
		voz_aux += frase;

		ui.tableWidget->insertColumn(ui.tableWidget->columnCount());
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setIcon(QIcon(".\\img\\silencio.png"));
		ui.tableWidget->setItem(fila, numero_compases, item);

		break;
	}

	case 3: {
		frase += "Calderon-";
		int fragmento = calderon->getFragmento();
		frase += to_string(fragmento) + " ";

		int longitud = calderon->getLongitud();
		frase += to_string(longitud) + "\n";

		int f_aux = ui.tabWidget->currentIndex();

		string voz_aux = voces[f_aux];
		voz_aux += frase;

		ui.tableWidget->insertColumn(ui.tableWidget->columnCount());
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setIcon(QIcon(".\\img\\calderon.png"));
		ui.tableWidget->setItem(fila, numero_compases, item);

		break;
	}


	}

	numero_compases++;
}


void QtGuiApplication1::on_play_clicked() {
	fstream archivo("Partitura.txt");

	string texto_partitura = "";

	if (voces_size > 1) {
		for (int i = 0; i < voces_size -1; i++) {
			texto_partitura += voces[i];
			texto_partitura += "Fin voz\n";
		}
		texto_partitura += voces[voces_size - 1];
	}
	else {
		texto_partitura = voces[0];
	}




	if (!archivo.is_open()) {
		archivo.open("Partitura.txt", ios::out);
	}

	archivo << texto_partitura << endl;

	archivo.close();


	//Generamos archivo MIDI

	string line;
	string texto;
	ifstream myfile("Partitura.txt");

	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			texto += line + "\n";
		}
		//cout << texto << endl;
		myfile.close();
	}
	Partitura p(texto);

	//cout << "Creada partitura" << endl;
	MIDIfile file;
	//cout << "Creado MIDIfile" << endl;
	file.crearMidiDePartitura(p, 9);
	//cout << "finalizado MIDIdePartitura" << endl;

	int pos_fin_voz = 0;
	pos_fin_voz = p.getFinVoz();

	while (pos_fin_voz != 0) {

		texto = texto.substr(p.getFinVoz());
		Partitura pnew(texto);
		file.addPartitura(pnew, 9);
		pos_fin_voz = pnew.getFinVoz();
	}



	/*
	bool t = true;
	while (t) {
	char c;
	cout << "Añadir track? (s/n)" << endl;
	cin >> c;
	if (c == 'n') {
	t = false;
	}
	else {
	Partitura pnew();
	file.addPartitura(pnew, 9);
	}
	}
	*/
	file.finish();
	char fileOutput[50];


	//cout << "Introduzca el nombre del archivo deseado" << endl;
	//cin >> fileOutput;

	FILE* fp = fopen("prueba.mid", "wb");
	std::fwrite(&file.at(0), 1, file.size(), fp);
	std::fclose(fp);


	//cout << "Midi creado." << std::endl;
	//cout << file.getNTracks() << std::endl;

	//system("pause");
	//return 0;
}
