/*
 * Logger.h
 *
 *  Created on: Sep 28, 2014
 *      Author: javier
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <iostream>
#include "../fifo/FifoEscritura.h"


class Logger {
public:

	Logger(std::string name);
	void log(std::string mensaje);
	void log(std::string mensaje, int param, ...);
	virtual ~Logger();

private:
	Serializador serializador;
	std::string id;
	FifoEscritura  fifo;
	int pid;
	std::string getTime();
	void replace(std::string & cadena,int pos, int valor);
};

#endif /* LOGGER_H_ */
