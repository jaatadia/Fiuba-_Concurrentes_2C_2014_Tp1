/*
 * Expendio.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Expendio.h"
#include "src/constantes.h"
Expendio::Expendio() {
	this->com = new ViaDoble(PATH_FIFOVENTA,false,false);

}

Expendio::~Expendio() {
	delete this->com;
}

