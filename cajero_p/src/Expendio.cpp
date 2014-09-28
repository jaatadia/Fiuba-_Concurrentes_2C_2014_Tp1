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

	this->com =new ViaDoble(PATH_FIFOVENTA,false,false, true);

}

Expendio::~Expendio() {
	delete this->com;
}

void Expendio::esperarCliente() {
	Mensaje* mje = com->recibir();
	cout<< "recibido " << mje->getTipo() << endl;
	delete mje;
}

void Expendio::darBoleto() {
	new Mensaje();


}
