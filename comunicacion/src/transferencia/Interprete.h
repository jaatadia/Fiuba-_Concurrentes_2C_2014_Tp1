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
	Interprete(string candena, string separador,char cantCampos);
	~Interprete();
	int getNextAsInt();
	string getNextAsStr();
};

#endif /* INTERPRETE_H_ */
