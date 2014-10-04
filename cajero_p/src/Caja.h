/*
 * Caja.h
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#ifndef CAJA_H_
#define CAJA_H_


/**
 * Clase para almacenar el dinero fuera de la memoria del proceso.
 */
class Caja {
public:
	Caja();
	~Caja();
	void almacenarDinero(int dinero);
};

#endif /* CAJA_H_ */
