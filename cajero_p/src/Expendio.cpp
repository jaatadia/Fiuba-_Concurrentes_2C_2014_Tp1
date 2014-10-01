/*
 * Expendio.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Expendio.h"
#include "src/constantes.h"
#include "src/fifo/ViaDoble.h"
#include <iostream>
#include "src/transferencia/Mensaje.h"
using namespace std;


Expendio::Expendio() {

	this->com =new ViaDoble(PATH_FIFOVENTA,false,false, false);
	this->com->setDuenio(true);
}

Expendio::~Expendio() {
	delete this->com;
}

void Expendio::esperarCliente() {
	Mensaje* mje = com->recibir();
	if(mje == NULL){
		com->cerrar();
		//cierro la cola y la abro para esperar que llegue alguien.
		com->abrir();
		mje = com->recibir();
	}
	delete mje;
}

void Expendio::darBoleto() {
	com->enviar(new Mensaje());
}
