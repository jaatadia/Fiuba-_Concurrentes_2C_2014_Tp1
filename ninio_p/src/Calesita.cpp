/*
 * Calesita.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Calesita.h"

Calesita::Calesita(Logger* log) : entrada(LOCK_ENTRADA),asientos(LOCK_ASIENTOS),salida(LOCK_SALIDA),ser(),fifoLec(PATH_FIFO_CALESITA_HACIA_NINOS,ser),fifoEsc(PATH_FIFO_CALESITA_HACIA_CALESITA,ser), log(log) {
	fifoEsc.abrir();
	fifoLec.abrir();
}

int Calesita::entrar(std::string boleto){

	log->log("Esperando lock");
	entrada.tomarLock();
	log->log("Lock conseguido, enviando boleto");
	fifoEsc.escribir(new MensajeString(boleto));
	log->log("Esperando respuesta del boleto");
	MensajeInt* msj = static_cast<MensajeInt*>(fifoLec.leer());
	int resultado = msj->getInt();
	entrada.liberarLock();
	log->log("Lock liberado");
	delete msj;
	return resultado;
}

int Calesita::sentarse(int asiento){
	asientos.tomarLock();
	//tomar asiento
	asientos.liberarLock();
	return asiento;
}

void Calesita::esperar(){
	//esperar semaforo para salir
}

void Calesita::salir(){
	salida.tomarLock();
	asientos.tomarLock();
	//levantarse del asiento
	//nose que mas
	asientos.liberarLock();
	salida.liberarLock();
}

Calesita::~Calesita() {
	fifoEsc.cerrar();
	fifoLec.cerrar();
}

