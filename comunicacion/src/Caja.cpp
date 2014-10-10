/*
 * Caja.cpp
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#include "Caja.h"

Caja::Caja() : saldo(MEMCOMP_ARCH,MEMCOMP_LETRA),lock_caja(LOCK_CAJA) {
}

Caja::~Caja() {
}

void Caja::almacenarDinero(int dinero) {
	lock_caja.tomarLock();
	int anterior= saldo.leer();
	saldo.escribir(anterior+dinero);
	lock_caja.liberarLock();
}

int Caja::consultarSaldo(){
	lock_caja.tomarLock();
	int monto = saldo.leer();
	lock_caja.liberarLock();
	return monto;
}
