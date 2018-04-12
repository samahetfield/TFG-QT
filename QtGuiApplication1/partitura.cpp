//
// Created by sergi on 10/11/2017.
//
/*
* partitura.cpp
*
*
*      Author: Zacarias
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;

class Baqueta {
	int tipo; // madera, fieltro, corcho y goma
	int dureza; // ligera, media, dura
public:
	Baqueta() {
		tipo = 0;
		dureza = 1;
	}

	Baqueta(int t, int d) {
		tipo = t;
		dureza = d;
	}

};

class Nota {
	int intensidad;
	int n_v; // nodo o vientre 0 = N3, 5 = V3, por defecto 2 = V1
	Baqueta b;
	double duracion; 	// 1 = nada
						// 0.5 = stacatto
						// 0.25 stacattissimo
	double sordina;	// Nivel de aplaque de nota
	double modTempo;
	int no = 35;
public:
	Nota() {
		intensidad = 0;
		n_v = 2;
		duracion = 1;
		sordina = 0;
		modTempo = 1;
	}


	Nota(int inten) {
		intensidad = inten;
		n_v = 2;
		duracion = 1;
		sordina = 0;
		modTempo = 1;
	}

	Nota(int inten, int nv, Baqueta ba) {
		intensidad = inten;
		n_v = nv;
		b = ba;
		duracion = 1;
		sordina = 0;
		modTempo = 1;
	}

	Nota(int inten, int nv) {
		intensidad = inten;
		n_v = nv;
		duracion = 1;
		sordina = 0;
		modTempo = 1;
	}

	Nota(int inten, int nv, int dur, double sor, double modT) {
		intensidad = inten;
		n_v = nv;
		duracion = dur;
		sordina = sor;
		modTempo = modT;
	}

	Nota(int inten, int nv, int dur, double sor, double modT, int n) {
		intensidad = inten;
		n_v = nv;
		duracion = dur;
		sordina = sor;
		modTempo = modT;
		no = n;
	}

	Nota(int inten, int nv, Baqueta ba, double dur) {
		intensidad = inten;
		n_v = nv;
		b = ba;
		duracion = dur;
		sordina = 0;
		modTempo = 1;
	}

	Nota(int inten, int nv, Baqueta ba, double dur, double sor) {
		intensidad = inten;
		n_v = nv;
		b = ba;
		duracion = dur;
		sordina = sor;
		modTempo = 1;
	}

	friend ostream& operator<<(ostream& os, Nota n)
	{
		os << n.intensidad << '/' << n.n_v;
		return os;
	}

	int getIntensidad() {
		return intensidad;
	}

	void setModTempo(int m) {
		modTempo = m;
	}

	double getModTempo() {
		return modTempo;
	}

	int getNota() {
		return no;
	}
};

enum TIPO_TREMOLO {
	NORMAL, GRADUAL, TIEMPO, INTENSIDAD
};
class Tremolo {
protected:
	TIPO_TREMOLO tipo;
	int inicio;
	int final;
	int modificador_tempo[2];
	vector<int> inten;
	vector<int> nv;
	int no = 35;


public:
	Tremolo(TIPO_TREMOLO ti, int in, int fin, int mod0, int mod1, vector<int> intensidades, vector<int> n_v) {
		tipo = ti;
		inicio = in;
		final = fin;
		//inten.resize(final-inicio);
		//nv.resize(final-inicio);
		modificador_tempo[0] = mod0;
		modificador_tempo[1] = mod1;
		inten = intensidades;
		nv = n_v;
	}

	Tremolo(TIPO_TREMOLO ti, int in, int fin, int mod0, int mod1, vector<int> intensidades, vector<int> n_v, int nota) {
		tipo = ti;
		inicio = in;
		final = fin;
		//inten.resize(final-inicio);
		//nv.resize(final-inicio);
		modificador_tempo[0] = mod0;
		modificador_tempo[1] = mod1;
		inten = intensidades;
		nv = n_v;
		no = nota;
	}
	void toString() {
		cout << "El tremolo es:" << endl;
		cout << "Tipo:" << tipo << endl;
		cout << "Inicio:" << inicio << endl;
		cout << "Final:" << final << endl;
		cout << "Inicio:" << inicio << endl;
		cout << "Mod0:" << modificador_tempo[0] << endl;
		cout << "Mod1:" << modificador_tempo[1] << endl;
		cout << "Intensidades size: " << inten.size() << endl;
		cout << "Nv size: " << nv.size() << endl;
	}

	vector<Nota> parse() {
		vector<Nota> res;
		if (tipo == NORMAL) {
			cout << "Entro en normal" << endl;
			for (int i = 0;i<final;i++) {
				for (int j = 0;j<modificador_tempo[0];j++) { // TODO: modificar tempo, hacer media de notas
					double modif = modificador_tempo[0];


					int intensidadFinal;
					if (inten[i] < inten[i + 1]) {
						intensidadFinal = inten[i] + (j*((inten[i + 1] - inten[i]) / modif));
					}
					else intensidadFinal = inten[i] - (i*((inten[i] - inten[i + 1]) / modif));
					Nota aux(intensidadFinal, nv[i], 1, 1, modif, no);

					//Nota aux(inten[i],nv[i], 1, 1, modif, no);
					res.push_back(aux);
				}
			}
		}
		else if (tipo == GRADUAL) {

		}
		else if (tipo == TIEMPO) {
			if (modificador_tempo[0] < modificador_tempo[1]) {
				double tamBloque = (inicio) / (modificador_tempo[1] - modificador_tempo[0]);

				for (int i = modificador_tempo[0];i<modificador_tempo[1];i++) {
					double v = i;
					double start = 1 / v;
					double t = ((tamBloque - start)*(v + 0.5)) + 1;
					double auxx = ((1 / v) - (1 / (v + 1))) / t;
					for (int j = 0;j<t;j++) {
						Nota aux(inten[i], nv[i], 1, 1, v, no);
						res.push_back(aux);
						start -= auxx;
						v = 1 / start;
					}
				}
			}
			else {
				double tamBloque = (inicio) / (modificador_tempo[0] - modificador_tempo[1]);

				for (int i = modificador_tempo[0];i>modificador_tempo[1];i--) {
					double v = i;
					double start = 1 / v;
					double t = ((tamBloque - start)*(v - 0.5));
					double auxx = ((1 / (v - 1)) - (1 / (v))) / t;
					for (int j = 0;j<t;j++) {
						Nota aux(inten[i], nv[i], 1, 1, v, no);
						res.push_back(aux);
						start += auxx;
						v = 1 / start;
					}
				}
			}
		}
		else if (tipo == INTENSIDAD) {
			for (int i = 0;i<final;i++) {
				double modif = modificador_tempo[0];

				Nota aux(inten[i], nv[i], 1, 1, modif, no);

				//Nota aux(inten[i],nv[i], 1, 1, modif, no);
				res.push_back(aux);
			}
		}

		return res;
	}
};


class Partitura {
	vector<Nota> notas;
	int pos_fin_voz = 0;
public:

	Partitura(string p) {
		string linea;


		int fin = 0;
		string p_aux = p;
		int fin_linea = 0;

		while (p.size() > fin) {
			int pos = p_aux.find("\n");

			if (pos != -1) {

				fin_linea = pos;
				string str3 = p_aux.substr(0, pos);

				//Sección que nos introduce una nota indicada en la partitura
				if (str3.find("Nota") != -1) {
					int intensidad = 0;
					int nodo = 0;
					int nota_aux = 0;
					int paso = 1;
					pos = p_aux.find("-");
					string spe = str3.substr(pos + 1);
					string aux = "";
					for (int i = 0; i < spe.size(); i++) { // En este bucle nos quedamos únicamente con las características de la nota
						if (spe.at(i) != ' ')
							aux += spe.at(i);
						else {
							switch (paso) {
							case 1:
								paso = 2;
								intensidad = stoi(aux);	// Intenisidad de la nota
								break;
							case 2:
								paso = 3;
								nodo = stoi(aux); // Nodo
								break;
							}
							aux = "";
						}
					}

					nota_aux = stoi(aux); // Nota a reproducir

					Nota n_aux(intensidad, nodo, 1, 1, 1, nota_aux);
					notas.push_back(n_aux);
				}
				else if (str3.find("Tremolo") != -1) { // Esta es la parte que trabajaremos para la realización de los Tremolos
					int longi = 0;
					int ini = 0;
					int fin = 0;
					int volu = 0;
					int nota_aux = 0;
					int paso = 1;
					pos = p_aux.find("-");
					string spe = str3.substr(pos + 1);
					string aux = "";

					//Como hay diferentes tremolos, debemos conocer qué tremolo se va a realizar
					if (spe.find("Intensidad") != -1) {
						TIPO_TREMOLO t(INTENSIDAD);
						int inicio = 0, final;
						int modificador_tempo[2];
						int intensidad_ini, intensidad_fin;
						int nota_aux;

						int pos_tre = spe.find(' ');
						string tremo = spe.substr(pos_tre + 1);


						for (int i = 0; i < tremo.size(); i++) { // Una vez conocido el tipo de tremolo nos quedamos con sus características
							if (tremo.at(i) != ' ')
								aux += tremo.at(i);
							else {
								switch (paso) {
								case 1:
									paso = 2;
									final = stoi(aux); //Longitud del tremolo
									break;
								case 2:
									paso = 3;
									modificador_tempo[0] = stoi(aux); // Número de lineas de velocidad al inicio
									break;
								case 3:
									paso = 4;
									modificador_tempo[1] = stoi(aux); // Número de lineas de velocidad al final
									break;
								case 4:
									paso = 5;
									intensidad_ini = stoi(aux); // Intensidad del tremolo inicio
									break;
								case 5:
									paso = 6;
									intensidad_fin = stoi(aux); // Intensidad del tremolo final
									break;
								}
								aux = "";
							}
						}

						nota_aux = stoi(aux); // Nota a reproducir


						int intervalo_intensidades = 21;

						vector<int> intensidades;
						intensidades.resize(final + 1);
						double intervalo;

						if (intensidad_ini < intensidad_fin) {

							if (intensidad_ini < 1) {
								intensidad_ini = 1;
							}
							if (intensidad_fin > 6) {
								intensidad_fin = 6;
							}
							intensidad_ini = (intensidad_ini - 1)*intervalo_intensidades;
							intensidad_fin = (intensidad_fin)* intervalo_intensidades;
							intervalo = (intensidad_fin - intensidad_ini) / final;

							for (int i = 0; i<final + 1; i++) {
								intensidades[i] = intervalo * (i + 1);
							}
						}
						else {
							if (intensidad_fin < 1) {
								intensidad_fin = 1;
							}
							if (intensidad_ini > 6) {
								intensidad_ini = 6;
							}
							intensidad_ini = (intensidad_ini)*intervalo_intensidades;
							intensidad_fin = (intensidad_fin - 1) * intervalo_intensidades;
							intervalo = (intensidad_ini - intensidad_fin) / final;


							for (int i = 0; i<final + 1; i++) {
								intensidades[final - (i + 1)] = intervalo * (i + 1);
							}
						}

						vector<int> n_v(final, 2);
						Tremolo trem(t, inicio, final, modificador_tempo[0], modificador_tempo[1], intensidades, n_v, nota_aux);
						vector<Nota> aux = trem.parse();
						notas.insert(notas.end(), aux.begin(), aux.end());
					}
					else if (spe.find("Tiempo") != -1) {
						TIPO_TREMOLO t(TIEMPO);
						int inicio = 0, final = 0;

						int pos_tre = spe.find(' ');
						string tremo = spe.substr(pos_tre + 1);


						for (int i = 0; i < tremo.size(); i++) { // Una vez conocido el tipo de tremolo nos quedamos con sus características
							if (tremo.at(i) != ' ')
								aux += tremo.at(i);
							else {
								switch (paso) {
								case 1:
									paso = 2;
									longi = stoi(aux); //Longitud del tremolo
									break;
								case 2:
									paso = 3;
									ini = stoi(aux); // Número de lineas de velocidad al inicio
									break;
								case 3:
									paso = 4;
									fin = stoi(aux); // Número de lineas de velocidad al final
									break;
								case 4:
									paso = 5;
									volu = stoi(aux); // Intensidad del tremolo
									break;
								}
								aux = "";
							}
						}

						nota_aux = stoi(aux); // Nota a reproducir
						inicio = longi;
						final = longi;
						int modificador_tempo[2];
						modificador_tempo[0] = ini;
						modificador_tempo[1] = fin;
						int vol = 0;
						vol = volu;
						int nota = 0;
						nota = nota_aux;
						vector<int> intensidades(final + 1, vol);
						vector<int> n_v(final, 2);
						Tremolo trem(t, inicio, final, modificador_tempo[0], modificador_tempo[1], intensidades, n_v, nota);
						vector<Nota> aux = trem.parse();
						notas.insert(notas.end(), aux.begin(), aux.end());
					}
					else {
						TIPO_TREMOLO t(NORMAL);
						int inicio = 0, final;
						int modificador_tempo[2];
						int intensidad_ini, intensidad_fin;
						int nota_aux;

						int pos_tre = spe.find(' ');
						string tremo = spe.substr(pos_tre + 1);


						for (int i = 0; i < tremo.size(); i++) { // Una vez conocido el tipo de tremolo nos quedamos con sus características
							if (tremo.at(i) != ' ')
								aux += tremo.at(i);
							else {
								switch (paso) {
								case 1:
									paso = 2;
									final = stoi(aux); //Longitud del tremolo
									break;
								case 2:
									paso = 3;
									modificador_tempo[0] = stoi(aux); // Número de lineas de velocidad al inicio
									break;
								case 3:
									paso = 4;
									modificador_tempo[1] = stoi(aux); // Número de lineas de velocidad al final
									break;
								case 4:
									paso = 5;
									intensidad_ini = stoi(aux); // Intensidad del tremolo inicio
									break;
								case 5:
									paso = 6;
									intensidad_fin = stoi(aux); // Intensidad del tremolo final
									break;
								}
								aux = "";
							}
						}

						nota_aux = stoi(aux); // Nota a reproducir
						
						//cout << "Numero de lineas en tremolo" << endl;
						modificador_tempo[0]=intensidad_ini;
						modificador_tempo[1] = modificador_tempo[0];
						
						//int vol;
						//cout << "Introduce volumen" << endl;
						//cin >> vol;
			
						vector<int> intensidades;
						intensidades.resize(final + 1);
						for (int i = 0; i<final + 1; i++) {
							intensidades[i] = intensidad_ini;
						}
						vector<int> n_v(final, 2);
						Tremolo trem(t, inicio, final, modificador_tempo[0], modificador_tempo[1], intensidades, n_v, nota_aux);
						vector<Nota> aux = trem.parse();
						notas.insert(notas.end(), aux.begin(), aux.end());
					}

				}
				else if (str3.find("Calderon") != -1) {
					int numero_notas = 0;
					int tiempo = 0;
					int paso = 1;
					pos = p_aux.find("-");
					string spe = str3.substr(pos + 1);
					string aux = "";
					for (int i = 0; i < spe.size(); i++) {
						if (spe.at(i) != ' ')
							aux += spe.at(i);
						else {
							switch (paso) {
							case 1:
								paso = 2;
								numero_notas = stoi(aux); // Numero de notas anteriores que vamos a repetir
								break;
							}
							aux = "";
						}
					}

					tiempo = stoi(aux); // Tiempo que durará el tremolo


										//En el caso de que se indique que queremos repetir más notas de las que realmente hay anteriormente, repetiremos todo lo anterior
					if (notas.size() < numero_notas) {
						numero_notas = notas.size();
					}

					unsigned indice = notas.size();

					for (unsigned i = 0;i < tiempo;i++) {
						for (int j = indice - numero_notas; j < indice; j++) {
							notas.push_back(notas[j]);
						}
					}

				}
				else if (str3.find("Silencio") != -1) {
					Nota aux(0, 0, 1, 1, 1, 0);
					notas.push_back(aux);
				}
				else if (str3.find("Fin voz") != -1) {
					pos_fin_voz = p.find("Fin voz") + 8;
					break;
				}

				fin += fin_linea;

				p_aux = p_aux.substr(fin_linea + 1, p.size());
			}
			else {
				break;
			}

		}
	}


	Partitura() {
		bool b = true;
		while (b) {
			int opcion;
			cout << "Introducir nota(1), tremolo(2), calderón(3) o silencio(4)" << endl; // TODO: calderon
			cin >> opcion;

			if (opcion == 1) {
				int intensidad;
				cout << "Introducir intensidad(0-127)" << endl;
				cin >> intensidad;
				int n_v;
				cout << "Introducir nodo o vientre(2 por defecto)" << endl;
				cin >> n_v;
				int nota;
				cout << "Introduce nota (35: bombo, 38: caja, 42/44/46: hi-hat)" << endl;
				cin >> nota;
				int numero;
				Nota aux(intensidad, n_v, 1, 1, 1, nota);
				notas.push_back(aux);

			}
			else if (opcion == 2) {
				int tipoTremolo;
				cout << "Tipo de tremolo(0: NORMAL, 1: TIEMPO, 2: INTENSIDAD)" << endl;
				cin >> tipoTremolo;
				if (tipoTremolo == 0) {
					TIPO_TREMOLO t(NORMAL);
					int inicio = 0;
					int final;
					cout << "Introduce longitud" << endl;
					cin >> final;
					int modificador_tempo[2];
					if (t == NORMAL) {
						cout << "Numero de lineas en tremolo" << endl;
						cin >> modificador_tempo[0];
						modificador_tempo[1] = modificador_tempo[0];
					}
					//int vol;
					//cout << "Introduce volumen" << endl;
					//cin >> vol;
					int nota;
					cout << "Introduce nota (35: bombo, 38: caja, 42/44/46: hi-hat)" << endl;
					cin >> nota;
					vector<int> intensidades;
					intensidades.resize(final + 1);
					for (int i = 0; i<final + 1; i++) {
						cout << "Introduce punto control intensidad" << endl;
						cin >> intensidades[i];
					}
					vector<int> n_v(final, 2);
					Tremolo trem(t, inicio, final, modificador_tempo[0], modificador_tempo[1], intensidades, n_v, nota);
					vector<Nota> aux = trem.parse();
					notas.insert(notas.end(), aux.begin(), aux.end());
				}
				else if (tipoTremolo == 1) {
					TIPO_TREMOLO t(TIEMPO);
					int inicio, final;
					cout << "Introduce longitud:" << endl;
					cin >> inicio;
					final = inicio;
					int modificador_tempo[2];
					cout << "Numero de lineas tremolo inicio" << endl;
					cin >> modificador_tempo[0];
					cout << "Numero de lineas tremolo final" << endl;
					cin >> modificador_tempo[1];
					int vol;
					cout << "Introduce volumen" << endl;
					cin >> vol;
					int nota;
					cout << "Introduce nota (35: bombo, 38: caja, 42/44/46: hi-hat)" << endl;
					cin >> nota;
					vector<int> intensidades(final + 1, vol);
					vector<int> n_v(final, 2);
					Tremolo trem(t, inicio, final, modificador_tempo[0], modificador_tempo[1], intensidades, n_v, nota);
					vector<Nota> aux = trem.parse();
					notas.insert(notas.end(), aux.begin(), aux.end());
				}
				else {
					TIPO_TREMOLO t(INTENSIDAD);
					int inicio = 0, final;
					cout << "Introduce longitud:" << endl;
					cin >> final;
					int modificador_tempo[2];
					int intensidad_ini, intensidad_fin;
					cout << "Numero de lineas velocidad tremolo inicio (1-6)" << endl;
					cin >> modificador_tempo[0];
					cout << "Numero de lineas velocidad tremolo final (1-6)" << endl;
					cin >> modificador_tempo[1];
					cout << "Numero de lineas de intensidad en tremolo inicio (1-6)" << endl;
					cin >> intensidad_ini;
					cout << "Numero de lineas de intensidad en tremolo final (1-6)" << endl;
					cin >> intensidad_fin;
					int nota;
					cout << "Introduce nota (35: bombo, 38: caja, 42/44/46: hi-hat)" << endl;
					cin >> nota;

					int intervalo_intensidades = 21;

					vector<int> intensidades;
					intensidades.resize(final + 1);
					double intervalo;

					if (intensidad_ini < intensidad_fin) {

						if (intensidad_ini < 1) {
							intensidad_ini = 1;
						}
						if (intensidad_fin > 6) {
							intensidad_fin = 6;
						}
						intensidad_ini = (intensidad_ini - 1)*intervalo_intensidades;
						intensidad_fin = (intensidad_fin)* intervalo_intensidades;
						intervalo = (intensidad_fin - intensidad_ini) / final;

					}
					else {
						if (intensidad_fin < 1) {
							intensidad_fin = 1;
						}
						if (intensidad_ini > 6) {
							intensidad_ini = 6;
						}
						intensidad_ini = (intensidad_ini)*intervalo_intensidades;
						intensidad_fin = (intensidad_fin - 1) * intervalo_intensidades;
						intervalo = (intensidad_fin - intensidad_ini) / final;

					}

					for (int i = 0; i<final + 1; i++) {
						intensidades[i] = intervalo * (i + 1);
					}
					vector<int> n_v(final, 2);
					Tremolo trem(t, inicio, final, modificador_tempo[0], modificador_tempo[1], intensidades, n_v, nota);
					vector<Nota> aux = trem.parse();
					notas.insert(notas.end(), aux.begin(), aux.end());
				}
			}
			else if (opcion == 3) {
				int siz;
				int tamanio;
				cout << "Introduce el tamaño de partitura que queremos repeitr en el calderón" << endl;
				cout << "Número de notas: " << notas.size() << endl;
				cin >> siz;

				cout << "Introduce el tiempo que durará el calderón";
				cin >> tamanio;
				if (siz > notas.size()) {
					siz = notas.size();
				}

				unsigned indice = notas.size();

				for (unsigned i = 0;i<tamanio;i++) {
					for (int j = indice - siz; j<indice; j++) {
						notas.push_back(notas[j]);
					}
				}
			}
			else if (opcion == 4) {
				Nota aux(0, 0, 1, 1, 1, 0);
				notas.push_back(aux);

			}
			else b = false;
		}
	}

	void mostrarNotas() {
		for (unsigned i = 0;i<notas.size();i++) {
			cout << notas[i] << endl;
		}
	}

	vector<Nota> getNotas() {
		return notas;
	}

	int getFinVoz() {
		return pos_fin_voz;
	}
};