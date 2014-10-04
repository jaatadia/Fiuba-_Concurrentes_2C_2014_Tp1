/*
 * DineroInsuficienteException.cpp
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#include "DineroInsuficienteException.h"
#include <sstream>
DineroInsuficienteException::DineroInsuficienteException(int necesario, int disponible):Exception("No se pudo comprar el boleto","dinero insuficiente"),necesario(necesario),disponible(disponible) {

}

DineroInsuficienteException::~DineroInsuficienteException() {
}

int DineroInsuficienteException::getDisponible() const {
	return disponible;
}

int DineroInsuficienteException::getNecesario() const {
	return necesario;
}

string DineroInsuficienteException::what() const {
	ostringstream ss;
	ss<< "Dinero insuficiente para compar el boleto. Faltan $" << necesario - disponible;
	return ss.str();
}
