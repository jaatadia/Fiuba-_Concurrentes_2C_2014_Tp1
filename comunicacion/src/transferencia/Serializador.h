/*
 * Serializador.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef SERIALIZADOR_H_
#define SERIALIZADOR_H_

#include "Mensaje.h"
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//TODO REVISAR CUANTO ES EL MAXIMO DEL SISOP PARA ENVIAR.
static const size_t MAX_BUFFER = 524288;

class Serializador {
private:
	map<string, Mensaje*> mensajes;
public:
	Serializador();
	~Serializador();
	/**
	 * envia un mensaje al descriptor, consume el mensaje.
	 */
	void enviar(int fd, Mensaje * mje);

	/**
	 * lee un mensaje del descriptor, no mantiene referencia del mensaje.
	 */
	Mensaje * recibir(int fd);
};

#endif /* SERIALIZADOR_H_ */
