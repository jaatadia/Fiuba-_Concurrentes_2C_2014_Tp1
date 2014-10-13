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

	MensajeString* mje = static_cast<MensajeString*>(fifoLec.leer_timeout(TIMEOUT));
	if (mje==NULL){
		return false;
	}
	FifoEscritura esc(PATH_COLA+nombre+mje->serializar(),ser);
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

