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
	this->com = new ViaDoble(PATH_FIFOVENTA,true);

}

Boleteria::~Boleteria() {
	delete this->com;
}

int Boleteria::comprar(int dineroDisponible) {
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
	return boleto;
}

