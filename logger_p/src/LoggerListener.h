/*
 * LoggerListener.h
 *
 *  Created on: Sep 28, 2014
 *      Author: javier
 */

#ifndef LOGGERLISTENER_H_
#define LOGGERLISTENER_H_

#include "src/fifo/FifoLectura.h"
#include "src/fifo/FifoEscritura.h"
#include "src/seniales/EventHandler.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>

class LoggerListener {
public:
	const static long int BUFFLEN = 200;

	LoggerListener(std::string name);
	void listen();
	void mute();
	void resume();
	bool alive();
	virtual ~LoggerListener();

private:
	Serializador ser;
	FifoLectura fifo;//fifo del que se va a leer
	FifoEscritura fifoEsc;//fifo en modo escritura para mantenerlo abierto en modo escritura
	std::fstream file;
	int cont;
	int muted;
	bool live;

};

#endif /* LOGGERLISTENER_H_ */
