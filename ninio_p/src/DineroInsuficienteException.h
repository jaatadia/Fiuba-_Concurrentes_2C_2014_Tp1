/*
 * DineroInsuficienteException.h
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#ifndef DINEROINSUFICIENTEEXCEPTION_H_
#define DINEROINSUFICIENTEEXCEPTION_H_

#include "src/Exception.h"

class DineroInsuficienteException: public Exception {
private:
	int necesario, disponible;
public:
	DineroInsuficienteException(int necesario, int disponible);
	~DineroInsuficienteException();
	string what() const;
	int getDisponible() const;
	int getNecesario() const;
};

#endif /* DINEROINSUFICIENTEEXCEPTION_H_ */
