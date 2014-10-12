/*
 * Calesita.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Calesita.h"

Calesita::Calesita(Logger* log) : entrada(LOCK_ENTRADA),asientos(LOCK_ASIENTOS),salida(LOCK_SALIDA),ser(),fifoLec(PATH_FIFO_CALESITA_HACIA_NINOS,ser),fifoEsc(PATH_FIFO_CALESITA_HACIA_CALESITA,ser), log(log),semAsientos(PATH_ARCH_SEM_ASIENTOS.c_str(),0),semVuelta(PATH_ARCH_SEM_CALE.c_str(),0) {
	fifoEsc.abrir();
	fifoLec.abrir();
}

int Calesita::entrar(std::string boleto){

	entrada.tomarLock();
	log->log("Entregando boleto");
	fifoEsc.escribir(new MensajeString(boleto));
	log->log("Esperando respuesta del boleto");
	MensajeInt* msj = static_cast<MensajeInt*>(fifoLec.leer());
	int resultado = msj->getInt();
	entrada.liberarLock();
	delete msj;
	return resultado;
}

int Calesita::sentarse(int asiento){
	asientos.tomarLock();//elegir donde sentarme
	//TODO elegir en la memoria compartida el asiento
	log->log("Buscando Asiento");
	asientos.liberarLock();
	semAsientos.signal();//informar que me sente
	return asiento;
}

void Calesita::esperar(){
	semVuelta.wait();//espero a que termine la vuelta
}

void Calesita::salir(){

	asientos.tomarLock();//sacarme del asiento
	//TODO liberar en la memoria compartida el asiento
	asientos.liberarLock();
	salida.tomarLock();//encolarme en la salida
	salida.liberarLock();
	semAsientos.signal();//informar que sali

}

Calesita::~Calesita() {
	fifoEsc.cerrar();
	fifoLec.cerrar();
}

