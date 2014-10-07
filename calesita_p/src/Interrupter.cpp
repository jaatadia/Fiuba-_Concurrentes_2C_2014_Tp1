/*
 * Interrupter.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Interrupter.h"

Interrupter::Interrupter() : ser(),fifoEsc(PATH_FIFO_CALESITA_HACIA_CALESITA,ser), fifoLec(PATH_FIFO_CALESITA_TIMEOUT,ser){
	fifoEsc.abrir();
	fifoLec.abrir();
}

void Interrupter::reenviar(){
	Mensaje* msj = fifoLec.leer();
	if (msj->getTipo()==MENSAJE_VACIO) {
		delete msj;
		return;
	}
	sleep(CALESITA_TIMEOUT);//espero el timeout para que decirle a la calesita que no espere mas
	fifoEsc.escribir(msj);

}

Interrupter::~Interrupter() {
	fifoEsc.cerrar();
	fifoLec.cerrar();
	fifoLec.eliminar();
}

