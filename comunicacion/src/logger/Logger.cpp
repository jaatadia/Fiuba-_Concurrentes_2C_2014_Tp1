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
#include <stdio.h>
#include <stdarg.h>

Logger::Logger(std::string name) :
		id(name), fifo(PATH_FIFOLOG, this->serializador) {
	//conversion fea de un int a string.
	this->pid = getpid();
	//fifo.abrir();
}

Logger::~Logger() {
	//fifo.cerrar();

}

void Logger::log(std::string mensaje) {
	std::string temp = getTime();
	std::cout << temp << " " << this->pid<< " " << this->id << ": "
			<< mensaje << std::endl;
	//MensajeLog * mje = new MensajeLog(this->pid, id, temp, mensaje);
	//fifo.escribir(mje);
}

std::string Logger::getTime() {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	std::string ret = asctime(ltm);
	ret.resize(ret.length() - 1);
	return ret;
}

void Logger::log(std::string mensaje, int param, ...) {
	va_list Numbers;
	va_start(Numbers, param);
	for (int i = 0; i < param; ++i)
		this->replace(mensaje, i, va_arg(Numbers, int));
	va_end(Numbers);
	this->log(mensaje);
}

void Logger::replace(std::string & cadena, int pos, int valor) {

	ostringstream tokenB;
	tokenB << "<" << pos << ">";
	string token = tokenB.str();
	ostringstream valorB;
	valorB << valor;
	string valorS = valorB.str();
	size_t posS = cadena.find(token);
	if(posS == string::npos) return;
	cadena.erase(posS,token.length());
	cadena.insert(posS,valorS);

}
