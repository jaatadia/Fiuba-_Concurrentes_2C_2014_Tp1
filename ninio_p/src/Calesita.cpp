/*
 * Calesita.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Calesita.h"

Calesita::Calesita(int id,Logger* log) :
	id_ninio(id),
	entrada(LOCK_ENTRADA),
	asientos(LOCK_ASIENTOS),
	salida(LOCK_SALIDA),
	ser(),
	fifoLec(PATH_FIFO_CALESITA_HACIA_NINOS,ser),
	fifoEsc(PATH_FIFO_CALESITA_HACIA_CALESITA,ser),
	log(log),
	semAsientos(PATH_ARCH_SEM_ASIENTOS.c_str(),0),
	semVuelta(PATH_ARCH_SEM_CALE.c_str(),0)
	{
		fifoEsc.abrir();
		fifoLec.abrir();
	}

int Calesita::entrar(std::string boleto){

	entrada.tomarLock();
	log->log("(id:<0>) Entregando boleto",1,id_ninio);
	fifoEsc.escribir(new MensajeString(boleto));
	log->log("(id:<0>) Esperando respuesta del boleto",1,id_ninio);
	MensajeInt* msj = static_cast<MensajeInt*>(fifoLec.leer());
	int resultado = msj->getInt();
	entrada.liberarLock();
	delete msj;
	return resultado;
}

int Calesita::sentarse(int asiento){
	asientos.tomarLock();//elegir donde sentarme
	//TODO flor - elegir en la memoria compartida el asiento
	log->log("(id:<0>) Buscando Asiento",1,id_ninio);
	asientos.liberarLock();
	semAsientos.signal();//informar que me sente
	return asiento;
}

void Calesita::esperar(){
	semVuelta.wait();//espero a que termine la vuelta
}

void Calesita::salir(){

	asientos.tomarLock();//sacarme del asiento
	//TODO flor - liberar en la memoria compartida el asiento
	asientos.liberarLock();
	salida.tomarLock();//encolarme en la salida
	salida.liberarLock();
	semAsientos.signal();//informar que sali

}

Calesita::~Calesita() {
	fifoEsc.cerrar();
	fifoLec.cerrar();
}

