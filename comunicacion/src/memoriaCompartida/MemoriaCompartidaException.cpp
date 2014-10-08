/*
 * MemoriaCompartidaException.cpp
 *
 *  Created on: Oct 7, 2014
 */

#include "MemoriaCompartidaException.h"

MemoriaCompartidaException::MemoriaCompartidaException(string mje, string cause):Exception(mje,cause) {
}


MemoriaCompartidaException::~MemoriaCompartidaException() {
}

string MemoriaCompartidaException::what() const {

	return "Memoria Compartida: "+ getMensaje() + ": " + getCause();
}

