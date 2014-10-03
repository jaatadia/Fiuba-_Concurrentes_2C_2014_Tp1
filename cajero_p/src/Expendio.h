/*
 * Expendio.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef EXPENDIO_H_
#define EXPENDIO_H_
#include "src/fifo/ViaDoble.h"

/**
 * Clase que permite al cajero comunicarse con los clientes que lleguen.
 */

class Expendio {
private:
	ViaDoble * com;
public:
	Expendio();
	~Expendio();

	/**
	 * Se pone a la espera de un cliente
	 */
	void esperarCliente();

	/**
	 * Da el boleto al ciente.
	 */
	void darBoleto();

};

#endif /* EXPENDIO_H_ */
