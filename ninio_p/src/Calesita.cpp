/*
 * Calesita.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Calesita.h"

Calesita::Calesita() : entrada(LOCK_ENTRADA),asientos(LOCK_ASIENTOS),salida(LOCK_SALIDA),ser(),fifoLec(PATH_FIFO_CALESITA_HACIA_NINOS,ser),fifoEsc(PATH_FIFO_CALESITA_HACIA_NINOS,ser) {
	fifoEsc.abrir();
	fifoLec.abrir();
}

int Calesita::entrar(std::string boleto){
	entrada.tomarLock();
	fifoEsc.escribir(new MensajeString(boleto));
	MensajeInt* msj = static_cast<MensajeInt*>(fifoLec.leer());
	int resultado = msj->getInt();
	entrada.liberarLock();
	return resultado;
}

int Calesita::sentarse(int asiento){
	asientos.tomarLock();
	asientos.liberarLock();
	return asiento;
}

Calesita::~Calesita() {
	fifoEsc.cerrar();
	fifoLec.cerrar();
}

