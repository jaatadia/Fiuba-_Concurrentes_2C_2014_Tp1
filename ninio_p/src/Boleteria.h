/*
 * Boleteria.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef BOLETERIA_H_
#define BOLETERIA_H_
#include "src/fifo/ViaDoble.h"
#include "src/lock/LockFile.h"
/**
 * Clase que permite COMPRAR EL BOLETO AL CAJERO.
 */
class Boleteria {

private:
	ViaDoble com;
	LockFile lock;

public:
	Boleteria();
	~Boleteria();

	/**
	 * Se indica de cuanta plata dispone y si es suficiente, devuelve el numero de boleto.
	 * Sino lanza una excepcion.
	 */
	int comprar(int dineroDisponible);
};

#endif /* BOLETERIA_H_ */
