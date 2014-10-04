/*
 * MensajeLog.cpp
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#include "MensajeLog.h"
#include "../constantes.h"
#include "exception/ParseException.h"
#include "Interprete.h"
#include <sstream>
MensajeLog::MensajeLog(int pid,string id, string hora, string mensaje) :
		Mensaje(MENSAJE_LOG),pid(pid), id(id), hora(hora), mensaje(mensaje) {

}

MensajeLog::~MensajeLog() {
}




Mensaje* MensajeLog::deserializar(const string mje) const {
	Interprete i(mje,SEPARADOR,4);
	return new MensajeLog(i.getNextAsInt(),i.getNextAsStr(),i.getNextAsStr(),i.getNextAsStr());

}

string MensajeLog::serializar() const {
	ostringstream ss;
	ss << this->pid << SEPARADOR << this->id << SEPARADOR << this->hora << SEPARADOR << this->mensaje;
	return ss.str();
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

const int MensajeLog::getPid() const {
	return pid;
}
