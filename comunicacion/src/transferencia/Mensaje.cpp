/*
 * Mensaje.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Mensaje.h"
#include "../constantes.h"
Mensaje::Mensaje(string tipo) {
	this->tipo = tipo;

}

string Mensaje::getTipo() const {
	return tipo;
}

Mensaje::Mensaje(): tipo(MENSAJE_VACIO) {
}

Mensaje::~Mensaje() {
}


Mensaje * Mensaje::deserializar(string const contenido) const {
	return new Mensaje(*this);
}

Mensaje::Mensaje(const Mensaje & m) {
	this->tipo = m.getTipo();
}

void Mensaje::operator =(const Mensaje& m) {
	this->tipo = m.tipo;
}

string Mensaje::serializar() const {
	return "v";
}
