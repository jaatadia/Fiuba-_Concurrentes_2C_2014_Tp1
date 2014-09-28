/*
 * ViaDoble.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "ViaDoble.h"
#include "../lock/FileLock.h"


ViaDoble::ViaDoble(const string nombre, const bool inlock, const bool outlock) {
	string nombreIn = nombre + "-" + IN_POSTFIX;
	string nombreOut = nombre + "-" + OUT_POSTFIX;
   	this->in = inlock ? new FifoLectura(nombreIn,new FileLock(nombreIn)) : new FifoLectura(nombreIn);
   	this->out = outlock ? new FifoEscritura(nombreOut,new FileLock(nombreOut)) : new FifoEscritura(nombreOut);
}

ViaDoble::~ViaDoble() {
	delete this->in;
	delete this->out;
}

void ViaDoble::enviar(Mensaje& mje) {
	//this->out->escribir(mje); TODO CAMBIAR LA FIFO PARA QUE USEN EL SERIALIZADOR.

}

Mensaje* ViaDoble::recibir() {
}
