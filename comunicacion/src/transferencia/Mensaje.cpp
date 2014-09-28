/*
 * Mensaje.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Mensaje.h"

Mensaje::Mensaje(char tipo) {
	this->tipo = tipo;

}

char Mensaje::getTipo() const {
	return tipo;
}

void Mensaje::setTipo(char tipo) {
	this->tipo = tipo;
}

