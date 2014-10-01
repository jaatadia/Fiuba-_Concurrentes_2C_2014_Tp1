/*
 * LoggerListener.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: javier
 */

#include "LoggerListener.h"
#include "src/constantes.h"
#include "src/transferencia/Mensaje.h"
#include "src/transferencia/MensajeLog.h"
LoggerListener::LoggerListener(std::string name) : file(), cont(0), muted(0){
	this->ser = new Serializador();
	fifo= new FifoLectura(PATH_FIFOLOG, *ser);
	fifoEsc= new FifoEscritura( name + "_fifo", *ser),
	file.open(name.c_str(),std::ios::app | std::ios::out);
}

LoggerListener::~LoggerListener() {
	fifo->cerrar();
	fifo->eliminar();
	fifoEsc->cerrar();
	fifoEsc->eliminar();
	delete fifo;
	delete fifoEsc;
	delete ser;
	file.close();

}

void LoggerListener::start(){
	fifo->abrir();
	fifoEsc->abrir();
}

void LoggerListener::listen() {

	Mensaje* mje = fifo->leer();
	if (mje == NULL){
		return;
	}
	MensajeLog * mjeLog = (MensajeLog*) mje;
	if (!muted){
		file<< mjeLog->getHora() << " " <<mjeLog->getId()<< ": " << mjeLog->getMensaje() << std::endl;
	}
	std::cout<< mjeLog->getHora() << " " <<mjeLog->getId()<< ": " << mjeLog->getMensaje() << std::endl;
}

void LoggerListener::mute(){
	muted = 1;
}
void LoggerListener::resume(){
	muted = 0;
}

int LoggerListener::alive(){
	return cont == 0;
}

int LoggerListener::handleSignal(int signum){
		cont = 1;
		std::cout<<"Ending Logger"<<std::endl;
		return 0;
}
