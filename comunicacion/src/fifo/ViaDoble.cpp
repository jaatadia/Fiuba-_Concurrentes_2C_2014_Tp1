/*
 * ViaDoble.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "ViaDoble.h"
#include "../lock/FileLock.h"

ViaDoble::ViaDoble(const string nombre, bool inversa) :
		duenio(false), abierta(false), inversa(inversa) {

	string nombreIn = nombre + "-" + (inversa ? OUT_POSTFIX : IN_POSTFIX);
	string nombreOut = nombre + "-" + (inversa ? IN_POSTFIX : OUT_POSTFIX);
	this->ser = new Serializador();
	this->in = new FifoLectura(nombreIn, *ser);
	this->out = new FifoEscritura(nombreOut, *ser);
}

ViaDoble::~ViaDoble() {
	this->in->cerrar();
	this->out->cerrar();
	if (duenio) {
		this->in->eliminar();
		this->out->eliminar();
	}

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

bool ViaDoble::isDuenio() const {
	return duenio;
}

void ViaDoble::setDuenio(bool duenio) {
	this->duenio = duenio;
}

void ViaDoble::cerrar() {
	abierta = false;
	if (this->inversa) {
		this->out->cerrar();
		this->in->cerrar();
	} else {
		this->in->cerrar();
		this->out->cerrar();
	}
}

void ViaDoble::abrir() {
	abierta = true;
	if (this->inversa) {
		this->out->abrir();
		this->in->abrir();
	} else {
		this->in->abrir();
		this->out->abrir();
	}
}
