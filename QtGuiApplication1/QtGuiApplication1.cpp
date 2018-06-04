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
	

	// Creamos una lista con cada uno de los instrumentos disponibles en la lista desplegable
	QStringList list = (QStringList() << "Bombo" << "Caja" << "Hit-Hat (abierto)" << "Hit-Hat (cerrado)" << "Aro de caja" << "Rimshot" << "Base (Goliat)" << "Hit-Hat (pedal)" << "Tom 1" << "Tom 2" << "Tom 3" << "Crash" << "Ride (campana)" << "Ride" << "Splash" << "Cencerro");
	ui.comboBox->addItems(list);

	//Establecemos la ruta en la que se encuentran los iconos y posteriormente asignamos esos iconos a cada botón correspondiente
	 nota_icon = new QIcon(QPixmap(".\\img\\nota.png"));
	 tremolo_icon = new QIcon(QPixmap(".\\img\\tremolo.png"));
	 silencio_icon = new QIcon(QPixmap(".\\img\\silencio.png"));
	 calderon_icon= new QIcon(QPixmap(".\\img\\calderon.png"));
	 play_icon = new QIcon(QPixmap(".\\img\\play.png"));
	 deshacer_icon = new QIcon(QPixmap(".\\img\\deshacer.png"));

	ui.button_nota->setIcon(*nota_icon);
	ui.button_tremolo->setIcon(*tremolo_icon);
	ui.button_silencio->setIcon(*silencio_icon);
	ui.button_calderon->setIcon(*calderon_icon);
	ui.play->setIcon(*play_icon);
	ui.deshacer_button->setIcon(*deshacer_icon);

	ui.pushButton->setEnabled(false);

	// Inicializamos los arrays en los que iremos almacenando la información de la partitura
	voces = new string[1];
	tab_voz = new QTableWidget*[1];
	tab_voz[0] = ui.tableWidget;
	voces_size = 1;
}

// Método que se llamará para deshacer la última acción realizada
void QtGuiApplication1::on_deshacer_button_clicked() {
	int f_aux = ui.tabWidget->currentIndex();
	QTableWidget *tab_select = tab_voz[f_aux];
	tab_select->removeColumn(f_aux);
	string voz = voces[f_aux];					// En voz almacenamos todo lo que hay escrito actualmente en esa voz
	string voz_nueva = "";
	int pos_fin = 0;

	/*
	 En el bucle comenzaremos a contar desde atrás hasta encontrar un salto de línea
	 Cuando encontremos el salto de línea, quiere decir que la última acción ya la hemos leído y 
	 por lo tanto ese fragmento del string es el que debemos borrar
	*/
	
	for (int i = voz.size() - 2; i > 0 && pos_fin == 0; i--) {
		if (voz.at(i) == '\n') {
			pos_fin = i;
		}
	}

	if (pos_fin == 0) {
		voz_nueva = "";
	}
	else {
		voz_nueva = voz.substr(0, pos_fin+1);
	}

	voces[f_aux] = voz_nueva;

}


void QtGuiApplication1::on_button_nota_clicked() {
	nota = new NotaDialog(this);
	nota->show();
	boton_pulsado = 0;
	ui.pushButton->setEnabled(true);
}

void QtGuiApplication1::on_button_tremolo_clicked() {
	tremolo = new TremoloDialog(this);
	tremolo->show();
	boton_pulsado = 1;
	ui.pushButton->setEnabled(true);

}

void QtGuiApplication1::on_button_silencio_clicked() {
	silencio = new SilencioDialog(this);
	silencio->show();
	boton_pulsado = 2;
	ui.pushButton->setEnabled(true);

}

void QtGuiApplication1::on_button_calderon_clicked() {
	calderon = new CalderonDialog(this);
	int f_aux = ui.tabWidget->currentIndex();

	QTableWidget *tab_select = tab_voz[f_aux];

	int maximum = tab_select->colorCount();
	calderon->setMax(maximum);
	calderon->show();
	boton_pulsado = 3;
	ui.pushButton->setEnabled(true);

}

//Este método nos servirá para crear una nueva voz

void QtGuiApplication1::on_nueva_voz_clicked() {
	//Primero crearemos un nuevo QTableWidget que añadiremos al TabWidget padre
	QWidget *nuevo_w = new QWidget();
	QTableWidget *nueva_voz = new QTableWidget(6,0,nuevo_w);		
	nueva_voz->setGeometry(10, 10, 850, 230);					// Establecemos las dimensiones de la tabla

	ui.tabWidget->addTab(nuevo_w, QString("Voz %0").arg(ui.tabWidget->count() +1));	// La añadimos creando una nueva pestaña

	QTableWidget **tab_aux = new QTableWidget*[voces_size+1];	//Redimensionamos el vector de cada TabWidget

	for (int i = 0; i < voces_size; i++) {
		tab_aux[i] = tab_voz[i];
	}

	tab_aux[voces_size] = nueva_voz;

	delete[] tab_voz;
	tab_voz = tab_aux;

	string *aux = new string[voces_size + 1]; //Redimensionamos el vector que almacenará la partitura de cada voz

	for (int i = 0; i < voces_size; i++) {
		aux[i] = voces[i];
	}

	delete[] voces;
	voces = aux;
	voces_size++;
	ui.pushButton->setEnabled(false);

}



// Método con el que crearemos el String de la acción indicada
void QtGuiApplication1::on_pushButton_clicked() {
	string midi_instrumento = "";
	string instrumento;
	int fila = 0;
	frase = "";
	
	//Comprobamos cuál es la acción que ha realizado el usuario
	switch (boton_pulsado)
	{
	case 0: {
		/*
			En el caso de ser una Nota, comenzaremos a crear el String.
			El programa debe recibir un string del estilo
						Nota-127 2 35
			Por lo que empezaremos a rellenar el string con "Nota" seguido de los valores introducidos por el usuario
		*/
		frase += "Nota-";
		int intensidad = nota->getIntensidad();
		frase += to_string(intensidad) + " ";

		int nodo = nota->getNodo();
		frase += to_string(nodo) + " ";


		//Obtendremos el intrumento que el usuario desea y dependiendo del elegido, tendremos que crear el identificador MIDI.
		instrumento = (ui.comboBox->currentText()).toUtf8().constData();


		if (instrumento == "Bombo") {
			midi_instrumento = "35";
		}
		else if (instrumento == "Aro de caja") {
			midi_instrumento = "37";
		}
		else if (instrumento == "Caja") {
			midi_instrumento = "38";
		}
		else if (instrumento == "Rimshot") {
			midi_instrumento = "39";
		}
		else if (instrumento == "Base (Goliat)") {
			midi_instrumento = "41";
		}
		else if (instrumento == "Hit-Hat (cerrado)") {
			midi_instrumento = "42";
		}
		else if (instrumento == "Hit-Hat (pedal)") {
			midi_instrumento = "44";
		}
		else if (instrumento == "Tom 1") {
			midi_instrumento = "45";
		}
		else if (instrumento == "Hit-Hat (abierto)") {
			midi_instrumento = "46";
		}
		else if (instrumento == "Tom 2") {
			midi_instrumento = "48";
		}
		else if (instrumento == "Crash") {
			midi_instrumento = "49";
		}
		else if (instrumento == "Tom 3") {
			midi_instrumento = "52";
		}
		else if (instrumento == "Ride (campana)") {
			midi_instrumento = "54";
		}
		else if (instrumento == "Splash") {
			midi_instrumento = "55";
		}
		else if (instrumento == "Cencerro") {
			midi_instrumento = "56";
		}
		else if (instrumento == "Ride") {
			midi_instrumento = "59";
		}


		frase += midi_instrumento + "\n";


		//Finalmente, dependiendo de la intensidad, se le asignará una fila a la nota, para introducir la nota en esa fila del hexagrama
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

		//Almacenamos en el vector de voces el string creado
		voces[f_aux] = voz_aux;

		//Añadimos esta nota a la partitura
		QTableWidget *tab_select = tab_voz[f_aux];
		QString ins_tab = QString::fromStdString(instrumento);

		tab_select->insertColumn(tab_select->columnCount());
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setIcon(*nota_icon);
		item->setText(ins_tab);
		tab_select->setItem(fila, (tab_select->columnCount())-1, item);

		break;
	}

	case 1: {
		/*
		En el caso de ser una Nota, comenzaremos a crear el String.
		El programa debe recibir un string del estilo
		Tremolo-5 3 6 1 6 38
		Por lo que empezaremos a rellenar el string con "Tremolo" seguido de los valores introducidos por el usuario
		*/
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

			//Obtenemos el instrumento deseado y creamos su identificador MIDI
			instrumento = (ui.comboBox->currentText()).toUtf8().constData();

			if (instrumento == "Bombo") {
				midi_instrumento = "35";
			}
			else if (instrumento == "Aro de caja") {
				midi_instrumento = "37";
			}
			else if (instrumento == "Caja") {
				midi_instrumento = "38";
			}
			else if (instrumento == "Rimshot") {
				midi_instrumento = "39";
			}
			else if (instrumento == "Base (Goliat)") {
				midi_instrumento = "41";
			}
			else if (instrumento == "Hit-Hat (cerrado)") {
				midi_instrumento = "42";
			}
			else if (instrumento == "Hit-Hat (pedal)") {
				midi_instrumento = "44";
			}
			else if (instrumento == "Tom 1") {
				midi_instrumento = "45";
			}
			else if (instrumento == "Hit-Hat (abierto)") {
				midi_instrumento = "46";
			}
			else if (instrumento == "Tom 2") {
				midi_instrumento = "48";
			}
			else if (instrumento == "Crash") {
				midi_instrumento = "49";
			}
			else if (instrumento == "Tom 3") {
				midi_instrumento = "52";
			}
			else if (instrumento == "Ride (campana)") {
				midi_instrumento = "54";
			}
			else if (instrumento == "Splash") {
				midi_instrumento = "55";
			}
			else if (instrumento == "Cencerro") {
				midi_instrumento = "56";
			}
			else if (instrumento == "Ride") {
				midi_instrumento = "59";
			}

			frase += midi_instrumento + "\n";

			int f_aux = ui.tabWidget->currentIndex();

			string voz_aux = voces[f_aux];
			voz_aux += frase;
			
			//Finalmente añadimos esta nueva acción al String de la partitura de esa voz y representamos la nueva acción en pantalla
			voces[f_aux] = voz_aux;


			QTableWidget *tab_select = tab_voz[f_aux];
			QString ins_tab = QString::fromStdString(instrumento);

			tab_select->insertColumn(tab_select->columnCount());
			QTableWidgetItem* item = new QTableWidgetItem;
			item->setIcon(*tremolo_icon);
			item->setText(ins_tab);
			tab_select->setItem(fila, (tab_select->columnCount()) - 1, item);


		break;
	}


	case 2: {

		/*
		En el caso de ser un Silencio, comenzaremos a crear el String.
		El programa debe recibir un string del estilo
		Silencio
		Por lo que empezaremos crearemos tantas líneas de silencio como el usuario haya indicado
		*/
		int longitud;

		for (int i = 0; i < silencio->getLongitud(); i++) {
			frase += "Silencio\n";
		}

		int f_aux = ui.tabWidget->currentIndex();

		string voz_aux = voces[f_aux];
		voz_aux += frase;

		//Añadiremos estas nuevas líneas al string de la partitura de es a voz y lo representamos por pantalla
		voces[f_aux] = voz_aux;


		QTableWidget *tab_select = tab_voz[f_aux];
		QString ins_tab = QString::fromStdString(std::to_string(silencio->getLongitud()));

		tab_select->insertColumn(tab_select->columnCount());
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setIcon(*silencio_icon);
		item->setText(ins_tab);
		tab_select->setItem(fila, (tab_select->columnCount()) - 1, item);

		break;
	}

	case 3: {
		/*
		En el caso de ser un Calderon, comenzaremos a crear el String.
		El programa debe recibir un string del estilo
		Calderon-4 3
		Por lo que empezaremos a rellenar el string con "Calderon" seguido de los valores introducidos por el usuario
		*/
		frase += "Calderon-";
		int fragmento = calderon->getFragmento();
		frase += to_string(fragmento) + " ";

		int longitud = calderon->getLongitud();
		frase += to_string(longitud) + "\n";

		int f_aux = ui.tabWidget->currentIndex();

		string voz_aux = voces[f_aux];
		voz_aux += frase;

		//Finalmente añadiremos esta nueva acción al string de esta voz y lo representaremos por pantalla
		voces[f_aux] = voz_aux;


		QTableWidget *tab_select = tab_voz[f_aux];
		QString ins_tab = QString::fromStdString(std::to_string(longitud));


		tab_select->insertColumn(tab_select->columnCount());
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setIcon(*calderon_icon);
		item->setText(ins_tab);
		tab_select->setItem(fila, (tab_select->columnCount()) - 1, item);

		break;
	}


	}
	ui.pushButton->setEnabled(false);
	numero_compases++;
}


//Método que será llamado cuando el usuario pulse el botón para almacenar el archivo MIDI
void QtGuiApplication1::on_play_clicked() {
	guardar = new Almacenar(this);	//Llamaremos al explorador de archivos para que el usuario indique dónde guardar el archivo
	guardar->show();

	string filepath = guardar->getPath();	//Obtendremos la ruta en la que almacenar el archivo


	
	int tempo_part = ui.tempoBox->value();

	int tempo_bpm = (tempo_part * 500) / 180;	//Obtenemos el tempo de la partitura que ha indicado el usuario

	fstream archivo("Partitura.txt");	//Creamos un archivo de texto

	string texto_partitura = "";

	//En esta parte obtendremos un string general con el contenido de todas las voces creadas anteriormente,
	// separando el contenido de cada voz por la frase "Fin voz"
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

	//Introduciremos este string en el archivo de texto y lo cerramos
	archivo << texto_partitura << endl;

	archivo.close();


	//Generamos archivo MIDI
	string line;
	string texto;
	ifstream myfile("Partitura.txt");

	if (myfile.is_open())
	{
		while (!myfile.eof())	//Leemos todo el archivo de texto
		{
			getline(myfile, line);
			texto += line + "\n";
		}
		myfile.close();
	}
	Partitura p(texto);	//Creamos la partitura de la primera voz 

	MIDIfile file(tempo_bpm, 1000000);	//Creamos un MIDIFile con el tempo que indica el usuario
	file.crearMidiDePartitura(p, 9);	//Llamamos al método para crear la partitura con el objeto de partitura creado anteriormente

	int pos_fin_voz = 0;			
	pos_fin_voz = p.getFinVoz();		//Obtenemos dónde se encuentra la frase "Fin voz" 

	while (pos_fin_voz != 0) {

		texto = texto.substr(pos_fin_voz);	//Creamos un nuevo string sin la voz añadida
		Partitura pnew(texto);				//Creamos una nueva partitura
		file.addPartitura(pnew, 9);			// Añadimos esta partitura al archivo MIDI creado anteriormente
		pos_fin_voz = pnew.getFinVoz();		//Obtenemos la nueva posición de fin voz
	}

	file.finish();
	char fileOutput[50];

	FILE* fp = fopen(filepath.c_str(), "wb");		//Almacenamos el archivo en el directorio indicado por el usuario
	std::fwrite(&file.at(0), 1, file.size(), fp);
	std::fclose(fp);

	remove("Partitura.txt");					//Eliminamos el archivo de texto creado.

	close();
}
