/*
 * Interprete.cpp
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#include "Interprete.h"

#include <sstream>
#include "exception/ParseException.h"
Interprete::Interprete(string cadena, string separador,char cantCampos): cadena(cadena),posActual(0), separador(separador),cantCampos(cantCampos),campoActual(1) {

}

Interprete::~Interprete() {

}

int Interprete::getNextAsInt() {
	string value = this->nextValue();
	return this->strToInt(value);
}

size_t Interprete::nextpos() {

	if(campoActual == cantCampos){
		return this->cadena.length();
	}
	size_t pos = cadena.find(this->separador,posActual);
	if (pos == string::npos && campoActual != cantCampos) {
		throw ParseException("Error parseando un campo de un mensaje.");
	}
	return pos;

}

string Interprete::nextValue() {
	size_t pos = cadena.find(this->separador,posActual);
	string result = cadena.substr(posActual, pos - posActual);
	posActual = pos+separador.length();
	campoActual++;
	return result;
}

string Interprete::getNextAsStr() {
	return this->nextValue();
}
string Interprete::intToStr(int nro) {
	ostringstream ss;
	ss << nro;
	return ss.str();

}

int Interprete::strToInt(string& cadena) {
	int number;
	if ( ! (istringstream(cadena) >> number) ) number = -1;
	return number;
}
