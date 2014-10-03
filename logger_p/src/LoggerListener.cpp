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
LoggerListener::LoggerListener(std::string fileName) : fifo(PATH_FIFOLOG,this->ser),fifoEsc(PATH_FIFOLOG, ser),file(), cont(0), muted(0){
	file.open(fileName.c_str(),std::ios::app | std::ios::out);
	fifo.abrir();
	fifoEsc.abrir();
}

LoggerListener::~LoggerListener() {
	fifo.cerrar();
	fifo.eliminar();
	fifoEsc.cerrar();
	fifoEsc.eliminar();
	file.close();

}

void LoggerListener::listen() {

	Mensaje* mje = fifo.leer();
	if (mje == NULL){
		return;
	}
	MensajeLog * mjeLog = (MensajeLog*) mje;
	if (!muted){
		file<< mjeLog->getHora() << " " <<mjeLog->getId()<< ": " << mjeLog->getMensaje() << std::endl;
	}
	std::cout<< mjeLog->getHora() << " " <<mjeLog->getId()<< ": " << mjeLog->getMensaje() << std::endl;
	delete mjeLog;
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
