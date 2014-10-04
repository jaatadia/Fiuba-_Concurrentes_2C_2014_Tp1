/*
 * Boleteria.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Boleteria.h"
#include "src/constantes.h"
#include "src/transferencia/MensajeCompraBoleto.h"
#include "src/InterrumpidoException.h"
#include "DineroInsuficienteException.h"
Boleteria::Boleteria() {
	this->com = new ViaDoble(PATH_FIFOVENTA,false);
	this->lock = new LockFile(com->getNombreEntrada());
}

Boleteria::~Boleteria() {
	delete this->lock;
	delete this->com;
}

int Boleteria::comprar(int dineroDisponible) {
	//me aseguro de obtener el lock para acceder al cajero.
	this->lock->tomarLock();
	this->com->abrir();
	com->enviar(new MensajeCompraBoleto(dineroDisponible));
	MensajeCompraBoleto* mje = (MensajeCompraBoleto*)com->recibir();
	if(mje == NULL){
		//TODO SE PUDRIO ALGO ACA SEGURO.
	}
	com->cerrar();
	int boleto = mje->getNroBoleto();
	int precio = mje->getImporte();
	delete mje;
	if(precio > dineroDisponible){
		throw DineroInsuficienteException(precio,dineroDisponible);
	}
	//libero el lock.
	this->lock->liberarLock();
	return boleto;
}

