/*
 * ColaController.h
 *
 *  Created on: Oct 13, 2014
 *      Author: javier
 */

#ifndef COLACONTROLLER_H_
#define COLACONTROLLER_H_
#include <string>
#include "fifo/FifoEscritura.h"
#include "fifo/FifoLectura.h"
#include "transferencia/Serializador.h"
#include "transferencia/MensajeString.h"
#include "constantes.h"

class ColaController {
private:
	std::string nombre;
	Serializador ser;
	FifoLectura fifoLec;//para leer
	FifoEscritura fifoEsc;//para mantener el de lectura abierto

public:
	ColaController(std::string name);
	bool next();
	virtual ~ColaController();
};

#endif /* COLACONTROLLER_H_ */
