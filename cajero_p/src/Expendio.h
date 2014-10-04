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
	int precio;
	FifoEscritura * fifoEsc;
public:
	Expendio(int precio);
	~Expendio();

	/**
	 * Espera a recibir el dinero de un ninio.
	 */
	int recibirNinio();

	/**
	 * Da el boleto al ninio.
	 */
	void darBoleto(int nroBoleto);

	/**
	 * No le da el boleto al ninio porque no tiene dinero suficiente (muy poli).
	 */
	void rechazarPagoInsuficiente();


};

#endif /* EXPENDIO_H_ */
