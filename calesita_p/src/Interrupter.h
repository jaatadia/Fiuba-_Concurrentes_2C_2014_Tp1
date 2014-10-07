/*
 * Interrupter.h
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#ifndef INTERRUPTER_H_
#define INTERRUPTER_H_

#include "src/constantes.h"
#include "src/transferencia/Serializador.h"
#include "src/transferencia/Mensaje.h"
#include "src/transferencia/MensajeInt.h"
#include "src/fifo/FifoEscritura.h"
#include "src/fifo/FifoLectura.h"


class Interrupter {
public:
	Interrupter();
	void reenviar();
	virtual ~Interrupter();

private:
	Serializador ser;
	FifoEscritura fifoEsc;
	FifoLectura fifoLec;
};

#endif /* INTERRUPTER_H_ */
