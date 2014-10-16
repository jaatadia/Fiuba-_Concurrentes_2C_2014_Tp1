/*
 * Cola.h
 *
 *  Created on: Oct 13, 2014
 *      Author: javier
 */

#ifndef COLA_H_
#define COLA_H_

#include <string>
#include "fifo/FifoEscritura.h"
#include "fifo/FifoLectura.h"
#include "transferencia/Serializador.h"
#include "transferencia/MensajeString.h"
#include "constantes.h"

class Cola {

private:
	std::string nombre;
	std::string id;
	Serializador ser;
	FifoEscritura fifoEsc;
	FifoLectura fifoLec;

public:
	Cola(std::string name, std::string id);
	void esperar();//una vez que se llama este metodo no devuelve el control hasta que sea su turno
	virtual ~Cola();
};

#endif /* COLA_H_ */
