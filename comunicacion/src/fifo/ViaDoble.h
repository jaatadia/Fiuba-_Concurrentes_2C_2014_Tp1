/*
 * ViaDoble.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef VIADOBLE_H_
#define VIADOBLE_H_
#include "FifoEscritura.h"
#include "FifoLectura.h"
#include <string>
#include "../transferencia/Mensaje.h"
using namespace std;

static const string IN_POSTFIX = "in";
static const string OUT_POSTFIX = "out";

/**
 * Permite tener una comunicacion sincronica doble via entre dos procesos.
 */
class ViaDoble {

private:
	FifoEscritura * out;
	FifoLectura * in;
public:
	ViaDoble(const string nombre, const bool inlock, const bool outlock);
	~ViaDoble();
	void enviar(Mensaje & mje);
	Mensaje * recibir();
};

#endif /* VIADOBLE_H_ */
