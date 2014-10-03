/*
 * MensajeLog.cpp
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#include "MensajeLog.h"
#include "../constantes.h"
#include "exception/ParseException.h"
MensajeLog::MensajeLog(string pid,string id, string hora, string mensaje) :
		Mensaje(MENSAJE_LOG),pid(pid), id(id), hora(hora), mensaje(mensaje) {

}

MensajeLog::~MensajeLog() {
}

Mensaje* MensajeLog::deserializar(const string mje) const {
	size_t pos = mje.find(SEPARADOR);
	if (pos == string::npos) {
		throw ParseException("Error deserializando un mensaje de log");
	}

	string pid = mje.substr(0, pos);

	size_t posAnt = pos + 1;
	pos = mje.find(SEPARADOR, posAnt);
	if (pos == string::npos) {
		throw ParseException("Error deserializando un mensaje de log");
	}
	string id = mje.substr(posAnt, pos - posAnt);

	posAnt = pos + 1;

	pos = mje.find(SEPARADOR, posAnt);
	if (pos == string::npos) {
		throw ParseException("Error deserializando un mensaje de log");
	}
	string hora = mje.substr(posAnt, pos - posAnt);


	string mensaje = mje.substr(pos+1,mje.length() - pos);

	return new MensajeLog(pid,id,hora,mensaje);

}

string MensajeLog::serializar() const {
	return this->pid + SEPARADOR + this->id + SEPARADOR + this->hora + SEPARADOR + this->mensaje;

}

const string& MensajeLog::getHora() const {
	return hora;
}

const string& MensajeLog::getId() const {
	return id;
}

const string& MensajeLog::getMensaje() const {
	return mensaje;
}

const string& MensajeLog::getPid() const {
	return pid;
}
