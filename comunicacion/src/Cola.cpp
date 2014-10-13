/*
 * Cola.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: javier
 */

#include "Cola.h"

Cola::Cola(std::string name,std::string id) : nombre(name),id(id),ser(),fifoEsc(PATH_COLA+name,ser),fifoLec(PATH_COLA+name+id,ser){
}
void Cola::esperar(){
	fifoEsc.abrir();
	fifoEsc.escribir(new MensajeString(id));
	fifoLec.abrir();
	Mensaje* mje =fifoLec.leer();
	delete mje;
	fifoEsc.cerrar();
	fifoLec.cerrar();
	fifoLec.eliminar();
}
Cola::~Cola() {
}

