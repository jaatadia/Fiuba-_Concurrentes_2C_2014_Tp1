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
#include <iostream>

Serializador::Serializador() {
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_VACIO, new Mensaje()));
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_LOG, new MensajeLog(0,"","","")));
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_STRING, new MensajeString("")));
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_COMPRAVENTA, new MensajeCompraBoleto(0)));
	this->mensajes.insert(pair<string, Mensaje*>(MENSAJE_NUMERO, new MensajeInt(0)));

}

Serializador::~Serializador() {
	for (std::map<string,Mensaje*>::iterator it=mensajes.begin(); it!=mensajes.end(); ++it)
	   delete it->second;
}

void Serializador::enviar(int fd, Mensaje * mje) {

	//armo el mensaje inicial.
	string serializacion = mje->getTipo() + mje->serializar()+SEPARADOR_MENSAJES;
	size_t len = serializacion.size();

	//envio el mensaje
	int result = write(fd, serializacion.c_str(),len*sizeof(char));
	 if (result == ERR_CODE) {
	 	throw ComunicacionException("No se pudo enviar el mensaje",	string(strerror(errno)));
	 }

}

Mensaje* Serializador::recibir(int fd) {
	Mensaje * mje = NULL;
	if (misMensajes.empty()){
		char buffer[MAX_BUFFER];
		ssize_t recibidos = 0;
		recibidos = read(fd,static_cast<void*>(buffer), MAX_BUFFER);
		if (recibidos == ERR_CODE) {
			throw ComunicacionException("No se pudo recibir el mensaje",string(strerror(errno)));
		}else if(recibidos == 0){
			throw Exception("No se pudo recibir el mensaje","Mensaje vacio");
		}
		std::string mensaje = buffer;
		mensaje.resize(recibidos);
		while(mensaje.length()>0){
			string myMensaje = mensaje.substr(0,mensaje.find(SEPARADOR_MENSAJES));
			mensaje=mensaje.substr(mensaje.find(SEPARADOR_MENSAJES)+1);

			//siempre lo primero es el codigo.
			string claveMensaje=myMensaje.substr(0,1);
			std::map<string, Mensaje*>::iterator msjCreator = this->mensajes.find(claveMensaje);
			if (msjCreator != mensajes.end()) {
				mje = msjCreator->second->deserializar(myMensaje.substr(1));
				misMensajes.push_back(mje);
			} else {
				throw ComunicacionException("Se recibio un mensaje con clave invalida ",myMensaje);
			}
		}
	}
	mje = misMensajes.front();
	misMensajes.pop_front();
	return mje;
}
