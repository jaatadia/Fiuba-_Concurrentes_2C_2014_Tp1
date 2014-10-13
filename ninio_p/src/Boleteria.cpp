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
Boleteria::Boleteria() : com(PATH_FIFOVENTA,false),lock(com.getNombreEntrada()){
}

Boleteria::~Boleteria() {
}

int Boleteria::comprar(int dineroDisponible) {
	//me aseguro de obtener el lock para acceder al cajero.

	this->lock.tomarLock();
	com.enviar(new MensajeCompraBoleto(dineroDisponible));
	MensajeCompraBoleto* mje = (MensajeCompraBoleto*)com.recibir();
	if(mje == NULL){
		throw Exception("No llego respuesta ","Mensaje invalido");
	}
	int boleto = mje->getNroBoleto();
	int precio = mje->getImporte();
	delete mje;
	if(precio > dineroDisponible){
		throw DineroInsuficienteException(precio,dineroDisponible);
	}
	//libero el lock.
	this->lock.liberarLock();
	return boleto;
}

