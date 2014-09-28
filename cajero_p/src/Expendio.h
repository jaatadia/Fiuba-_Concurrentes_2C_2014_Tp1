/*
 * Expendio.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef EXPENDIO_H_
#define EXPENDIO_H_
#include "src/fifo/ViaDoble.h"


class Expendio {
private:
	ViaDoble * com;
public:
	Expendio();
	~Expendio();
	void esperarCliente();
	void darBoleto();

};

#endif /* EXPENDIO_H_ */
