/*
 * MensajeCompraBoleto.cpp
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#include "MensajeCompraBoleto.h"
#include "../constantes.h"
#include <sstream>
#include "Interprete.h"
MensajeCompraBoleto::MensajeCompraBoleto(int importe):Mensaje(MENSAJE_COMPRAVENTA),importe(importe),nroBoleto(NRO_BOLETO_INVALIDO) {

}

Mensaje* MensajeCompraBoleto::deserializar(const string contenido) const {
	Interprete i(contenido,SEPARADOR,2);
	MensajeCompraBoleto* msj = new MensajeCompraBoleto(i.getNextAsInt());
	msj->setNroBoleto(i.getNextAsInt());
	return msj;
}

int MensajeCompraBoleto::getImporte() const {
	return importe;
}

int MensajeCompraBoleto::getNroBoleto() const {
	return nroBoleto;
}

void MensajeCompraBoleto::setNroBoleto(int nroBoleto) {
	this->nroBoleto = nroBoleto;
}

string MensajeCompraBoleto::serializar() const {
	ostringstream ss;
	ss<<this->importe<<SEPARADOR<<this->nroBoleto;
	return ss.str();
}

MensajeCompraBoleto::~MensajeCompraBoleto() {
}

