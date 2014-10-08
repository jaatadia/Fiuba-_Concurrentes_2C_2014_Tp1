/*
 * Caja.h
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#ifndef CAJA_H_
#define CAJA_H_

#include "src/memoriaCompartida/MemoriaCompartida.h"
#include "src/constantes.h"

/**
 * Clase para almacenar el dinero fuera de la memoria del proceso.
 * Usa el template de MemoriaCompartida para poner el monto de la caja
 */
class Caja {
	private:
		MemoriaCompartida<int> saldo;
	public:
		Caja();
		~Caja();
		void almacenarDinero(int dinero);
		int consultarSaldo();
};

#endif /* CAJA_H_ */
