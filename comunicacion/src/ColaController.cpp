/*
 * ColaController.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: javier
 */

#include "ColaController.h"

ColaController::ColaController(std::string name): nombre(name),ser(),fifoLec(PATH_COLA+nombre,ser),fifoEsc(PATH_COLA+nombre,ser) {
	fifoLec.abrir();
	fifoEsc.abrir();
}

bool ColaController::next(){

	//recibo el id del fifo por el cual avisar que sigue
	MensajeString* mje = static_cast<MensajeString*>(fifoLec.leer_timeout(TIMEOUT));
	if (mje==NULL){
		//si no llego nadie devuelvo false
		return false;
	}

	//escribo por el fifo correspondiente el aviso de que es su turno
	FifoEscritura esc(PATH_COLA+nombre+mje->serializar(),ser);
	delete mje;

	esc.abrir();
	esc.escribir(new Mensaje());
	esc.cerrar();
	return true;
}

ColaController::~ColaController() {
	fifoEsc.cerrar();
	fifoLec.cerrar();
	fifoLec.eliminar();
}

