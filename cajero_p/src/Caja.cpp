/*
 * Caja.cpp
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#include "Caja.h"

Caja::Caja() : saldo(MEMCOMP_ARCH,MEMCOMP_LETRA) {
}

Caja::~Caja() {
}

void Caja::almacenarDinero(int dinero) {
	int anterior= saldo.leer();
	saldo.escribir(anterior+dinero);
}

int Caja::consultarSaldo(){
	return saldo.leer();
}
