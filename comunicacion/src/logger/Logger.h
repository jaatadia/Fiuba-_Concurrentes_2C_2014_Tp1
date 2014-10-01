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
	virtual ~Logger();

private:
	Serializador serializador;
	FifoEscritura  fifo;
	std::string id;
	string pid;
	std::string getTime();

};

#endif /* LOGGER_H_ */
