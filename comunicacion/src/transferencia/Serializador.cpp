/*
 * Serializador.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Serializador.h"
#include "../constantes.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "exception/ComunicacionException.h"
#include "../InterrumpidoException.h"
#include "MensajeLog.h"
#include "MensajeString.h"
#include "MensajeCompraBoleto.h"
#include "MensajeInt.h"

Serializador::Serializador() {
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_VACIO, new Mensaje()));
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_LOG, new MensajeLog(0,"","","")));
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_STRING, new MensajeString("")));
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_COMPRAVENTA, new MensajeCompraBoleto(0)));
	//this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_NUMERO, new MensajeInt()));

}

Serializador::~Serializador() {
	//TODO LIMPIAR EL MAPEO
}

void Serializador::enviar(int fd, Mensaje * mje) {

	//TODO HAY QUE TENER EN CUENTA QUE ESTO HACE DOS WRITES, SI NO SE BLOQUEA PARA QUE OTRO NO ESCRIBA, VA A FALLAR


	//armo el mensaje inicial.
	string serializacion = mje->getTipo() + mje->serializar();
	size_t len = serializacion.size();
	if(len > MAX_BUFFER){
		throw ComunicacionException("Mensaje demasiado largo", "El mensaje que se intenta enviar es demasiado largo");
	}
	const char* ser_cstr = serializacion.c_str();
	//envio la cantidad de caracteres.
	int result = write(fd, &len, sizeof(size_t));
	if (result == ERR_CODE) {
		throw ComunicacionException("No se pudo enviar el mensaje",string(strerror(errno)));
	}
	//Este codigo es por si llegamos a enviar mas de lo que el buffer del sistema permite


//	size_t enviados = 0;
//	int restantes;
	//comienzo el bucle (restantes = longitud total del mensaje;
//	while (enviados < len) {
//		restantes = len - enviados;
//		//Ahora intento enviar lo restante.
//		result = write(fd, &(ser_cstr[enviados]), restantes);
//		//Si da error cancelo
//		if (result == ERR_CODE) {
//			throw ComunicacionException("No se pudo enviar el mensaje",string(strerror(errno)));
//		}
//
//		//Sumo a los enviados lo que envié.
//		enviados += result;
//	}

	//Envio del mensaje.
	result = write(fd, ser_cstr, len);
	//Si da error cancelo
	if (result == ERR_CODE) {
		throw ComunicacionException("No se pudo enviar el mensaje",
				string(strerror(errno)));
	}
	if(size_t(result) < len) {
		throw ComunicacionException("No se pudo enviar el mensaje","Demasiado largo");
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
			if(errno == EINTR){
				throw InterrumpidoException("No se pudo recibir el mensaje","Interrumpido por señal");
			}
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
