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
#include "Proceso.h"
#include "Parametros.h"
using namespace std;

/**
 * Representacion de un proceso ageno al proceso actual.
 */
class Proceso {
private:
	int pid;
	void run(const string path, Parametros & params);
public:

	/**
	 * Crea un proceso con el ejecutable indicado.
	 * lanza excepcion si no pudo crear el proceso.
	 */
	Proceso(const string path, Parametros & params);
	Proceso(const string path);
	~Proceso();
	int getPid() const;
	void setPid(int pid);
};

#endif /* PROCESO_H_ */
