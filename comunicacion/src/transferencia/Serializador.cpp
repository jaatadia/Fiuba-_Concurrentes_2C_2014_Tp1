/*
 * Serializador.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Serializador.h"
#include "../constantes.h"
#include "MensajeLog.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "ComunicacionException.h"
Serializador::Serializador() {
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_VACIO, new Mensaje()));
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_LOG, new MensajeLog("","","","")));

}

Serializador::~Serializador() {
	//TODO LIMPIAR EL MAPEO
}

void Serializador::enviar(int fd, Mensaje * mje) {

	//TODO mensaje con errorn.

	//armo el mensaje inicial.
	string serializacion = mje->getTipo() + mje->serializar();
	size_t len = serializacion.size();
	if(len > MAX_BUFFER){
		throw ComunicacionException("Mensaje demasiado largo", "El mensaje que se intenta enviar es demasiado largo");
	}
	string ser_cstr = serializacion.c_str();
	size_t enviados = 0;
	int restantes;
	//envio la cantidad de caracteres.
	int result = write(fd, &len, sizeof(size_t));
	if (result == ERR_CODE) {
		throw ComunicacionException("No se pudo enviar el mensaje",string(strerror(errno)));
	}
	//comienzo el bucle (restantes = longitud total del mensaje;
	while (enviados < len) {
		restantes = len - enviados;
		//Ahora intento enviar lo restante.
		result = write(fd, &(ser_cstr[enviados]), restantes);
		//Si da error cancelo
		if (result == ERR_CODE) {
			throw ComunicacionException("No se pudo enviar el mensaje",string(strerror(errno)));
		}

		//Sumo a los enviados lo que envié.
		enviados += result;
	}
}

Mensaje* Serializador::recibir(int fd) {
		char buffer[MAX_BUFFER] = "";
		size_t longitudTotal;
		size_t recibidos = 0;

		//leo que longitud tiene el mensaje
		int result = read(fd, &longitudTotal, sizeof(size_t));

		if(result == 0){
			return NULL;
		}

		if (result == ERR_CODE) {
			throw ComunicacionException("No se pudo recibir el mensaje",string(strerror(errno)));
		}

		//va concatenando lo que puede leer.
		while (recibidos < longitudTotal) {
			result = read(fd, &(buffer[recibidos]), longitudTotal - recibidos);

			if (result == ERR_CODE) {
				throw ComunicacionException("No se pudo recibir el mensaje",string(strerror(errno)));
			}
			recibidos += result;
		}

		//siempre lo primero es el codigo.
		string claveMensaje=string(buffer).substr(0,1);

		Mensaje * mje = NULL;
		std::map<string, Mensaje*>::iterator msjCreator = this->mensajes.find(claveMensaje);
		if (msjCreator != mensajes.end()) {
			mje = msjCreator->second->deserializar(string(buffer+1));

		} else {
				throw ComunicacionException("Se recibio un mensaje invalido ","Clave de mensaje invalida " +claveMensaje);
		}
		return mje;
}
