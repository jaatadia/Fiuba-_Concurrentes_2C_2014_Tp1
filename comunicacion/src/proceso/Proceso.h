/*
 * Bifurcador.h
 *
 *  Created on: 25/9/2014
 *      Author: jonathan
 */

#ifndef PROCESO_H_
#define PROCESO_H_

#include <string>
#include "../constantes.h"
using namespace std;

class Proceso {
private:
	int pid;
public:

	/**
	 * Crea un proceso con el ejecutable indicado.
	 * lanza excepcion si no pudo crear el proceso.
	 */
	Proceso(const string path);
	~Proceso();
};

#endif /* PROCESO_H_ */
