/*
 * ViaDoble.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "ViaDoble.h"

ViaDoble::ViaDoble(const string nombre, bool duenio) :
		duenio(duenio), abierta(false) {

	string nombreIn = nombre + "-" + (duenio ? IN_POSTFIX : OUT_POSTFIX);
	string nombreOut = nombre + "-" + (duenio ? OUT_POSTFIX : IN_POSTFIX);
	this->serializador = new Serializador();
	this->in = new FifoLectura(nombreIn, *serializador);
	this->out = new FifoEscritura(nombreOut, *serializador);
}

ViaDoble::~ViaDoble() {
	if (this->abierta) {
		this->in->cerrar();
		this->out->cerrar();
	}
	if (duenio) {
		this->in->eliminar();
		this->out->eliminar();
	}

	delete this->in;
	delete this->out;
	delete this->serializador;
}

void ViaDoble::enviar(Mensaje * mje) {
	this->out->escribir(mje);

}

Mensaje* ViaDoble::recibir() {
	return this->in->leer();
}

void ViaDoble::cerrar() {
	abierta = false;
	if (this->duenio) {
		this->in->cerrar();
		this->out->cerrar();
	} else {
		this->out->cerrar();
		this->in->cerrar();
	}
}

void ViaDoble::abrir() {
	abierta = true;
	if (this->duenio) {
		this->in->abrir();
		this->out->abrir();
	} else {
		this->out->abrir();
		this->in->abrir();
	}
}

string ViaDoble::getNombreEntrada() {
	if (this->duenio) {
		return this->in->getNombre();
	}
	return this->out->getNombre();
}

Serializador* ViaDoble::getSerializador() const {
	return serializador;
}
