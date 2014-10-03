/*
 * Boleteria.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef BOLETERIA_H_
#define BOLETERIA_H_
#include "src/fifo/ViaDoble.h"

/**
 * Clase que permite COMPRAR EL BOLETO AL CAJERO.
 */
class Boleteria {

private:
	ViaDoble * com;


public:
	Boleteria();
	~Boleteria();
	void comprar();
};

#endif /* BOLETERIA_H_ */
