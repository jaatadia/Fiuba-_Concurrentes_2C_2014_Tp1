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

/**
 * Clase en cargada de la serializacion de los mensajes a traves del descriptor indicado
 * -El descriptir debe estar abierto para la operación que se desea realizar
 */
class Serializador {
private:
	map<string, Mensaje*> mensajes;
public:
	Serializador();
	~Serializador();
	/**
	 * Envia un mensaje al descriptor, libera la memoria del mensaje.
	 * -Si no pudo escribir el mensaje lanza ComunicacionException.
	 */
	void enviar(int fd, Mensaje * mje);

	/**
	 * Lee un mensaje del descriptor, la memoria debe ser liberada por el lector.
	 * -Si antes de recibir es interrumpido por una signal, lanza InterrumpidoException
	 * -Por cualquier otro error lanza ComunicacionException.
	 */
	Mensaje * recibir(int fd);
};

#endif /* SERIALIZADOR_H_ */
