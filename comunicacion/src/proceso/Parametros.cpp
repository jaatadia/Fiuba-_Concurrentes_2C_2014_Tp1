/*
 * Parametros.cpp
 *
 *  Created on: 8/10/2014
 *      Author: jonathan
 */

#include "Parametros.h"
#include <sstream>
#include <string.h>
Parametros::Parametros() {
	params.push_back(NULL);
}

void Parametros::push(unsigned int valor) {
	ostringstream ss;
	ss << valor;
	params.pop_back();
	string str = ss.str() ;
	char* value = new char[str.size()+1];
	strcpy(value, str.c_str());
	params.push_back(value);
	params.push_back(NULL);
}

void Parametros::push(const string& valor) {
	params.pop_back();
	char* value = new char[valor.size()+1];
	strcpy(value, valor.c_str());
	params.push_back(value);
	params.push_back(NULL);

}

Parametros::~Parametros() {
	params.pop_back();
	for (std::vector<char*>::iterator it = params.begin() ; it != params.end(); ++it){
		delete *it;
	}
}

void Parametros::pushFirst(unsigned int valor) {
	ostringstream ss;
	ss << valor;
	string str = ss.str() ;
	char* value = new char[str.size()+1];
	strcpy(value, str.c_str());
	vector<char *>::iterator it = params.begin();
	params.insert(it,value);
}

void Parametros::pushFirst(const string& valor) {
	char* value = new char[valor.size()+1];
	strcpy(value, valor.c_str());
	vector<char *>::iterator it = params.begin();
	params.insert(it,value);
}

char ** Parametros::getContenido() {
	return &params.front();
}

int Parametros::getSize() {
	return params.size();
}
