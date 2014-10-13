/*
 * Calesita.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Calesita.h"

Calesita::Calesita(int nro_de_ninio,Logger* log, int cant_asientos) :
	id_ninio(nro_de_ninio),
	entrada(LOCK_ENTRADA),
	asientos(LOCK_ASIENTOS),
	salida(LOCK_SALIDA),
	ser(),
	fifoLec(PATH_FIFO_CALESITA_HACIA_NINOS,ser),
	fifoEsc(PATH_FIFO_CALESITA_HACIA_CALESITA,ser),
	log(log),
	semAsientos(PATH_ARCH_SEM_ASIENTOS.c_str(),0),
	semVuelta(PATH_ARCH_SEM_CALE.c_str(),0),
	calesita_asientos(cant_asientos), //se attacha a la memoria compartida
	asiento_final(0)
	{
		fifoEsc.abrir();
		fifoLec.abrir();
	}

int Calesita::entrar(std::string boleto){

	entrada.tomarLock();
	log->log("(nro:<0>) Entregando boleto",1,id_ninio);
	fifoEsc.escribir(new MensajeString(boleto));
	log->log("(nro:<0>) Esperando respuesta del boleto",1,id_ninio);
	MensajeInt* msj = static_cast<MensajeInt*>(fifoLec.leer());
	int resultado = msj->getInt();
	entrada.liberarLock();
	delete msj;
	return resultado;
}

int Calesita::sentarse(int asiento){
	asientos.tomarLock(); //buscar el asiento

	log->log("(nro:<0>) Buscando Asiento",1,id_ninio);

	if ( calesita_asientos.estaOcupado(asiento) == 1 ){
		int i=0;
		while ( i < this->calesita_asientos.getCantidadAsientos() ){
			if (calesita_asientos.estaOcupado(i) == 0) {
				asiento_final = i;
			} else {
				i++;
			}
		}
	} else {
		//esta libre el q quiero, lo elijo
		asiento_final = asiento;
	}
	calesita_asientos.sentarme(asiento_final);

	asientos.liberarLock();
	semAsientos.signal();//informar que me sente
	return asiento;
}

void Calesita::esperar(){
	semVuelta.wait();//espero a que termine la vuelta
}

void Calesita::salir(){

	asientos.tomarLock();//sacarme del asiento
	calesita_asientos.levantarme(this->asiento_final);
	asientos.liberarLock();
	salida.tomarLock();//encolarme en la salida
	salida.liberarLock();
	semAsientos.signal();//informar que sali

}

Calesita::~Calesita() {
	fifoEsc.cerrar();
	fifoLec.cerrar();
}

