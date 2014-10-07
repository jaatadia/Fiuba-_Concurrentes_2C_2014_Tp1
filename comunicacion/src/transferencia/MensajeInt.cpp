/*
 * MensajeCompraBoleto.cpp
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#include "MensajeInt.h"
#include "../constantes.h"
#include <sstream>
#include "Interprete.h"
MensajeInt::MensajeInt(int numero):Mensaje(MENSAJE_NUMERO),numero(numero){

}

Mensaje* MensajeInt::deserializar(const string contenido) const {
	Interprete i(contenido,SEPARADOR,1);
	MensajeInt* msj = new MensajeInt(i.getNextAsInt());
	return msj;
}

int MensajeInt::getInt() const {
	return numero;
}

string MensajeInt::serializar() const {
	ostringstream ss;
	ss<<this->numero;
	return ss.str();
}

MensajeInt::~MensajeInt() {
}

