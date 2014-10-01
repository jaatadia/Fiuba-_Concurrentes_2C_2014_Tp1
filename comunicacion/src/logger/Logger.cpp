/*
 * Logger.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: javier
 */

#include "Logger.h"
#include "../constantes.h"
#include "../transferencia/MensajeLog.h"
#include <sys/unistd.h>
#include <unistd.h>
#include <sstream>
Logger::Logger(std::string name) :
		id(name) {
	//conversion fea de un int a string.
	std::ostringstream ss;
	ss << getpid();
	this->pid = ss.str();
	this->serializador = new Serializador();
	this->fifo = new FifoEscritura(PATH_FIFOLOG, *(this->serializador));
	fifo->abrir();
}

Logger::~Logger() {
	fifo->cerrar();
	delete fifo;
	delete serializador;

}

void Logger::log(std::string mensaje) {
	std::string temp = getTime();
	MensajeLog * mje = new MensajeLog(this->pid, id, temp, mensaje);
	fifo->escribir(mje);
}

std::string Logger::getTime() {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	std::string ret = asctime(ltm);
	ret.resize(ret.length() - 1);
	return ret;
}
