/*
 * Interprete.h
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#ifndef INTERPRETE_H_
#define INTERPRETE_H_
#include <string>
using namespace std;
/**
 * Sirve para parsear un un string separado por campos.
 */

class Interprete {
private:
	string cadena;
	size_t posActual;
	string separador;
	char cantCampos;
	char campoActual;
private:
	string nextValue();
	string intToStr(int);
	int strToInt(string &);
	size_t nextpos();
public:
	/**
	 * Cadena: el string a parsear
	 * Separador: el separador. (no probado si tiene mas de un caracter)
	 * CantCampos: la cantidad de campos que tiene el string.
	 */
	Interprete(string candena, string separador,char cantCampos);
	~Interprete();
	/**
	 * Proximo valor como entero
	 */
	int getNextAsInt();

	/**
	 * Proximo valor como string.
	 */
	string getNextAsStr();
};

#endif /* INTERPRETE_H_ */
