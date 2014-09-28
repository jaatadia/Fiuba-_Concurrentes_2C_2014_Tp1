/*
 * ViaDoble.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "ViaDoble.h"
#include "../lock/FileLock.h"


ViaDoble::ViaDoble(const string nombre, const bool inlock, const bool outlock, bool inPrimero) {
	string nombreIn = nombre + "-" + IN_POSTFIX;
	string nombreOut = nombre + "-" + OUT_POSTFIX;
	this->ser = new Serializador();
   	this->in = inlock ? new FifoLectura(nombreIn, *ser,new FileLock(nombreIn)) : new FifoLectura(nombreIn, *ser);
   	this->out = outlock ? new FifoEscritura(nombreOut,*ser,new FileLock(nombreOut)) : new FifoEscritura(nombreOut,*ser);
   	if(inPrimero){
   		this->in->abrir();
   		this->out->abrir();
   	} else {
   		this->out->abrir();
   		this->in->abrir();
   	}
}

ViaDoble::~ViaDoble() {
	delete this->in;
	delete this->out;
	delete this->ser;
}

void ViaDoble::enviar(Mensaje * mje) {
	this->out->escribir(mje);

}

Mensaje* ViaDoble::recibir() {
	return this->in->leer();
}
