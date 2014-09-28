/*
 * Serializador.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef SERIALIZADOR_H_
#define SERIALIZADOR_H_

#include "Mensaje.h"

class Serializador {
public:
	Serializador();
	~Serializador();
	/**
	 * envia un mensaje al descriptor
	 */
	void enviar(int fd, Mensaje & mje);

	/**
	 * lee un mensaje del descriptor.
	 */
	Mensaje * recibir(int fd);
};

#endif /* SERIALIZADOR_H_ */
