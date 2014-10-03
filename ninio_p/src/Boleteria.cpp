/*
 * Boleteria.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Boleteria.h"
#include "src/constantes.h"
Boleteria::Boleteria() {
	this->com = new ViaDoble(PATH_FIFOVENTA,true);

}

Boleteria::~Boleteria() {
	delete this->com;
}

void Boleteria::comprar() {
	this->com->abrir();
	com->enviar(new Mensaje());
	Mensaje* mje = com->recibir();
	com->cerrar();
	delete mje;
}

