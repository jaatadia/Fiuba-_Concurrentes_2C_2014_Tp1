/*
 * MensajeString.cpp
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#include "MensajeString.h"


MensajeString::MensajeString(string msj):mensaje(msj) {

}

Mensaje* MensajeString::deserializar(const string contenido) const {
	return new MensajeString(contenido);
}

string MensajeString::serializar() const {
	return this->mensaje;
}

MensajeString::~MensajeString() {
}

