/*
 * Bifurcador.h
 *
 *  Created on: 25/9/2014
 *      Author: jonathan
 */

#ifndef BIFURCADOR_H_
#define BIFURCADOR_H_

#include <string.h>
using namespace std;

class Bifurcador {
public:
	Bifurcador();
	/**
	 * Crea un proceso con el ejecutable indicado.
	 * lanza excepcion si no pudo crear el proceso.
	 */
	void crearHijo(const string path) const;
	~Bifurcador();
};

#endif /* BIFURCADOR_H_ */
