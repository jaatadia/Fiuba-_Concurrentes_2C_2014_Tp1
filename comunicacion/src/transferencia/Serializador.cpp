/*
 * Serializador.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Serializador.h"
#include "../constantes.h"

Serializador::Serializador() {
	this->mensajes.insert(pair<char, Mensaje*>(MENSAJE_VACIO, new Mensaje()));

}

Serializador::~Serializador() {
}

void Serializador::enviar(int fd, Mensaje * mje) {

	//TODO mensaje con errorn.

	//armo el mensaje inicial.
	string serializacion = mje->getTipo() + mje->serializar();
	size_t len = serializacion.size();
	if(len > MAX_BUFFER){
		throw "Mensaje demasiado largo";
	}
	string ser_cstr = serializacion.c_str();
	size_t enviados = 0;
	int restantes;
	//envio la cantidad de caracteres.
	int result = write(fd, &len, sizeof(size_t));
	if (result == -1) {
		throw "No se pudo enviar el mensaje";
	}
	//comienzo el bucle (restantes = longitud total del mensaje;
	while (enviados < len) {
		restantes = len - enviados;
		//Ahora intento enviar lo restante.
		result = write(fd, &(ser_cstr[enviados]), restantes);
		//Si da error cancelo
		if (result == -1) {
			throw "No se pudo enviar el mensaje";
		}

		//Sumo a los enviados lo que envié.
		enviados += result;
//			cout<< "Se enviaron "<< restantes<< "restantes  de " << enviados << "/"<<len<<endl;
	}
}

Mensaje* Serializador::recibir(int fd) {
		char buffer[MAX_BUFFER] = "";
		size_t longitudTotal;
		size_t recibidos = 0;

		//TODO MANEJAR ERRNO.
		//leo que longitud tiene el mensaje
		int result = read(fd, &longitudTotal, sizeof(size_t));

		if (result == -1) {
			throw "No se pudo recibir el mensaje del host";
		}

		//va concatenando lo que puede leer.
		while (recibidos < longitudTotal) {
			result = read(fd, &(buffer[recibidos]), longitudTotal - recibidos);

			if (result == -1) {
				throw "No se pudo recibir el mensaje del host";
			}
			recibidos += result;
		}

		//siempre lo primero es el codigo.
		char claveMensaje = buffer[0];

		Mensaje * mje = NULL;
		std::map<char, Mensaje*>::iterator msjCreator = this->mensajes.find(claveMensaje);
		if (msjCreator != mensajes.end()) {
			mje = msjCreator->second->deserializar(string(buffer+1));

		} else {
		 throw "Se recibio un mensaje invalido " + claveMensaje;
		}
		return mje;
}
