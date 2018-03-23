//
// Created by sergi on 10/11/2017.
//

/*
* midi.cpp
*
*
*      Author: Zacarias
*/

#include <iostream>// For std::cout
#include <vector>  // For std::vector
#include <cstring>
#include <string> // For std:strlen
#include <cstdio>  // For std::fopen, std::fwrite, std::fclose
#include <fstream>
#include <cstdlib>
#include "partitura.cpp"

using namespace std;


typedef unsigned char byte;

/* First define a custom wrapper over std::vector<byte>
* so we can quickly push_back multiple bytes with a single call.
*/
class MIDIvec : public std::vector<byte> {
public:
	// Methods for appending raw data into the vector:
	template<typename... Args>
	void addBytes(byte data, Args...args) {
		push_back(data);
		addBytes(args...);
	}

	template<typename... Args>
	void addBytes(const char* s, Args...args) {
		insert(end(), s, s + std::strlen(s));
		addBytes(args...);
	}

	void addBytes() {

	}
};

// Define a class which encodes MIDI events into a track


class MIDItrack : public MIDIvec {
protected:
	unsigned delay, runningStatus;
public:
	MIDItrack()
		: MIDIvec(), delay(0), runningStatus(0) {}

	// Mehthds for indicating how much time elapses:
	void addDelay(unsigned amount) {
		delay += amount;
	}

	void setDelay(unsigned amount) {
		delay = amount;
	}

	unsigned getDelay() {
		return delay;
	}

	void addVarLen(unsigned t) {
		if (t >> 21) addBytes(0x80 | ((t >> 21) & 0x7F));
		if (t >> 14) addBytes(0x80 | ((t >> 14) & 0x7F));
		if (t >> 7)  addBytes(0x80 | ((t >> 7) & 0x7F));
		addBytes(((t >> 0) & 0x7F));
	}

	void flush() {
		addVarLen(delay);
		//delay = 0;
	}

	// Methods for appending events into the track:

	template<typename... Args>
	void addEvent(byte data, Args...args) {
		/* MIDI tracks have the following strcuture:
		*
		* {timestamp [metaevent ... ] event } ...
		*
		* Each event is prefixed with a timestamp, which is encoded in a variable-length format.
		* The timestamp describes the amount of time that must be elapsed before this event can be handled.
		*
		* After this timestamp, comes the event data.
		* The first byte of the event alwayshas the high bit on, and the remaining bytes always have the high bit off.
		*
		* The first byte can howeber be omitted; in that case, it is assumed that the first byte is the same as in
		* the previous command. This is called "running status".
		* The event may furthermore be prefixed with a number of meta events.
		*
		* 	Length 		Description
		Variable 	deltaticks
		1 byte 		Type of event and channel
		1 byte 		Parameter 1
		1 byte 		Parameter 2
		*
		*
		* Types of events
		Value 	Name 				Parameter_1 	Parameter_2
		0x80  	NOTE-OFF 			Note 			Speed
		0x90  	NOTE-ON 			Note 			Speed
		0xA0  	NOTE-AFTERTOUCH 	Note 			Speed
		0xB0  	controlLER 			controller 		Value
		0xC0  	PROGRAM-CHANGE 		Program
		0xD0  	CHANNEL-AFTERTOUCH 	Speed
		0xE0  	PITCH-BEND 						Value
		0xF0  	SYSTEM-EXCLUSIVE
		0xFF  	Meta-event
		*/
		flush();
		if (data != runningStatus) addBytes(runningStatus = data);
		addBytes(args...);
	}

	void addEvent() {

	}
	/*  Meta Event Description
	*
	* 	Length 		Description
	Variable	deltaticks
	1 byte 		0xFF
	1 byte 		Type of metaevent
	Variable 	Length of the argument
	(Length) 	Value of the argument
	*
	* Types of metaevent:
	Value 	Name
	0x00 	Sequence number
	0x01 	Text event
	0x02 	Copyright notice
	0x03 	Sequence or track name
	0x04 	Instrument name
	0x05 	Lyric text
	0x06 	Marker text
	0x07 	Cue point
	0x08 	Program name
	0x09 	Device name
	0x20 	MIDI channel prefix assignment (obsoleto)
	0x21 	Port by default (obsoleto)
	0x2F 	End of track
	0x51 	Tempo (µs/♩)
	0x54 	Desplazamiento temporal SMPTE offset TODO
	0x58 	Indicación de compás Time signature TODO
	0x59 	Indicación de tonalidad Key signature TODO
	0x7F 	Reservado para el secuenciador Sequencer specific event TODO
	*
	*/
	template<typename... Args>
	void AddMetaEvent(byte metatype, byte nbytes, Args...args) {
		flush();
		addBytes(0xFF, metatype, nbytes, args...);
	}

	//Key-related parameters: channel number, note number, pressure
	void keyOn(int ch, int n, int p) {
		if (n >= 0)addEvent(0x90 | ch, n, p);
	}

	void keyOff(int ch, int n, int p) {
		if (n >= 0)addEvent(0x80 | ch, n, p);
	}

	void keyTouch(int ch, int n, int p) {
		if (n >= 0)addEvent(0xA0 | ch, n, p);
	}

	//Events with other types of parameters:
	void control(int ch, int c, int v) {
		addEvent(0xB0 | ch, c, v);
	}

	void patch(int ch, int patchno) {
		addEvent(0xC0 | ch, patchno);
	}

	void wheel(int ch, unsigned value) {
		addEvent(0xE0 | ch, value & 0x7F, (value >> 7) & 0x7F);
	}

	//Methods for appending metadata into the track:
	void addText(int texttype, const char* text) {
		AddMetaEvent(texttype, strlen(text), text);
	}

};

// Define a class that encapsulates all methods needed to craft a MIDI file.
class MIDIfile : public MIDIvec {
protected:
	std::vector<MIDItrack> tracks;
	// Tempo = tiempo que corresponde a una negra
	unsigned deltaticks, tempo;
public:
	MIDIfile()
		: MIDIvec(), tracks(), deltaticks(1000), tempo(1000000) {}

	MIDIfile(int delta, int temp)
		: MIDIvec(), tracks(), deltaticks(delta), tempo(temp) {}

	void addLoopStart() {
		(*this)[0].addText(6, "loopStart");
	}
	void addLoopEnd() {
		(*this)[0].addText(6, "loopEnd");
	}

	MIDItrack& operator[] (unsigned trackno) {
		if (trackno >= tracks.size()) {
			tracks.reserve(16);
			tracks.resize(trackno + 1);
		}

		MIDItrack& result = tracks[trackno];
		if (result.empty()) {
			// Meta 0x58 (misc settings):
			//		time signature: 4/2
			//		ticks/metro:	24
			//		32nd per 1/4:	8
			result.AddMetaEvent(0x58, 4, 4, 2, 24, 8);
			// Meta 0x51 (tempo):
			result.AddMetaEvent(0x51, 3, tempo >> 16, tempo >> 8, tempo);
		}

		return result;
	}

	void finish() {
		clear();
		addBytes(
			//MIDI signature (MThd and number 6)
			"MThd", 0, 0, 0, 6,
			/* Format number (0: one track
			* 				  1: multiple tracks, synchronous)
			* 				  2: multiple tracks, asynchronous)
			*/
			0, 1,
			// Number of tracks
			tracks.size() >> 8, tracks.size(),
			// Time division
			deltaticks >> 8, deltaticks);
		for (unsigned a = 0; a<tracks.size(); ++a) {
			// Add meta 0x2F to the track, indicating the track end:
			tracks[a].AddMetaEvent(0x2F, 0);
			//Add the track into the MIDI file:
			addBytes("MTrk",
				tracks[a].size() >> 24,
				tracks[a].size() >> 16,
				tracks[a].size() >> 8,
				tracks[a].size() >> 0);
			insert(end(), tracks[a].begin(), tracks[a].end());
		}
	}

	int getNTracks() {
		return tracks.size();
	}

	void crearMidiDePartitura(Partitura p, int ch) {
		tracks.resize(1);
		tracks[0].setDelay(160);
		int oDelay = 160;
		vector<Nota> aux = p.getNotas();
		cout << "Res.size: " << aux.size() << endl;
		for (unsigned i = 0;i<aux.size();i++) {
			if (aux[i].getIntensidad() >= 0) {
				tracks[0].setDelay(oDelay / aux[i].getModTempo());
				tracks[0].keyOn(ch, aux[i].getNota(), aux[i].getIntensidad());
				tracks[0].keyOff(ch, aux[i].getNota(), aux[i].getIntensidad());
			}
			else {
				if (aux[i].getIntensidad() == -1) tracks[0].setDelay(tracks[0].getDelay() / aux[i].getModTempo());
				else tracks[0].setDelay(oDelay);
			}
		}
		tracks[0].keyOn(ch, aux[aux.size() - 1].getNota(), 0);
	}

	void addPartitura(Partitura p, int ch) {
		tracks.resize(getNTracks() + 1);
		int indice = getNTracks() - 1;
		tracks[indice].setDelay(160);
		int oDelay = 160;
		vector<Nota> aux = p.getNotas();
		for (unsigned i = 0;i<p.getNotas().size();i++) {
			if (aux[i].getIntensidad() >= 0) {
				tracks[indice].setDelay(oDelay / aux[i].getModTempo());
				tracks[indice].keyOn(ch, aux[i].getNota(), aux[i].getIntensidad());
				tracks[indice].keyOff(ch, aux[i].getNota(), aux[i].getIntensidad());
			}
			else {
				if (aux[i].getIntensidad() == -1) tracks[indice].setDelay(tracks[indice].getDelay() / aux[i].getModTempo());
				else tracks[indice].setDelay(oDelay);
			}
		}
		tracks[indice].keyOn(ch, aux[aux.size() - 1].getNota(), 0);
	}
};


/*MIDIfile crearMidiDePartitura(Partitura p, int ch) {
MIDIfile res;
res[0].setDelay(160);
int oDelay = 160;
vector<Nota> aux = p.getNotas();
cout << "Res.size: " << aux.size() << endl;
for(unsigned i=0;i<p.getNotas().size();i++) {
if (aux[i].getIntensidad() >=0) {
res[0].setDelay(oDelay/aux[i].getModTempo());
res[0].keyOn(ch, aux[i].getNota(), aux[i].getIntensidad());
res[0].keyOff(ch, aux[i].getNota(), aux[i].getIntensidad());
} else {
if(aux[i].getIntensidad() == -1) res[0].setDelay(res[0].getDelay()/aux[i].getModTempo());
else res[0].setDelay(oDelay);
}
}
res[0].keyOn(ch, aux[aux.size()-1].getNota(), 0);
return res;
}

void addPartitura(MIDIfile &m, Partitura p, int ch) {
int indice = m.getNTracks();
m[indice].setDelay(160);
int oDelay = 160;
vector<Nota> aux = p.getNotas();
for(unsigned i=0;i<p.getNotas().size();i++) {
if (aux[i].getIntensidad() >=0) {
m[indice].setDelay(oDelay/aux[i].getModTempo());
m[indice].keyOn(ch, aux[i].getNota(), aux[i].getIntensidad());
m[indice].keyOff(ch, aux[i].getNota(), aux[i].getIntensidad());
} else {
if(aux[i].getIntensidad() == -1) m[indice].setDelay(m[m.getNTracks()].getDelay()/aux[i].getModTempo());
else m[indice].setDelay(oDelay);
}
}
tracks[indice].keyOn(ch, aux[aux.size()-1].getNota(), 0);
}
*/


/*
int play() {
	/*
	MIDIfile file(1000,1000000);
	file.addLoopStart();
	Partitura platillo;
	Partitura bombo;
	Partitura caja;
	file[0].setDelay(160);
	file[1].setDelay(160);
	file[2].setDelay(160);

	vector<Nota> aux;
	// canal 9 percusion: drum kit
	for(int i=0;i<128;i++) {
	if (i%8==0) {
	file[0].keyOn(9, 35, 127); // bombo
	} else file[0].keyOn(9, 42, 0);
	if ((i+4)%8==0) {
	file[1].keyOn(9, 38, 100); // caja
	} else file[1].keyOn(9,38,0); // hi-hat cerrado
	file[2].keyOn(9,42, 127);
	}

	file.finish();
	*


	string line;
	string archivo;
	ifstream myfile("Partitura.txt");

	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			archivo += line + "\n";
		}
		cout << archivo << endl;
		myfile.close();
	}
	else
		cout << "Unable to open file";



	Partitura p(archivo);


	cout << "Creada partitura" << endl;
	MIDIfile file;
	cout << "Creado MIDIfile" << endl;
	file.crearMidiDePartitura(p, 9);
	cout << "finalizado MIDIdePartitura" << endl;

	int pos_fin_voz = 0;
	pos_fin_voz = p.getFinVoz();

	while (pos_fin_voz != 0) {

		archivo = archivo.substr(p.getFinVoz());
		Partitura pnew(archivo);
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
	*
	file.finish();
	char fileOutput[50];



	cout << "Introduzca el nombre del archivo deseado" << endl;
	cin >> fileOutput;

	FILE* fp = fopen(fileOutput, "wb");
	fwrite(&file.at(0), 1, file.size(), fp);
	fclose(fp);

	cout << "Midi creado." << std::endl;
	cout << file.getNTracks() << std::endl;

	system("pause");
	return 0;
}
*/