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
#include "src/Exception.h"
LoggerListener::LoggerListener(std::string fileName) :
		fifo(PATH_FIFOLOG, this->ser), fifoEsc(PATH_FIFOLOG, ser), file(), cont(
				0), muted(0), live(true) {
	file.open(fileName.c_str(), std::ios::app | std::ios::out);
	fifo.abrir();
	fifoEsc.abrir();
}

LoggerListener::~LoggerListener() {
	fifo.cerrar();
	fifoEsc.cerrar();
	fifoEsc.eliminar();
	file.close();

}

bool LoggerListener::alive(){
	return live;
}

void LoggerListener::listen() {
		Mensaje* mje = fifo.leer();
		if (mje == NULL) {
			return;
		}

		if(mje->getTipo()==MENSAJE_VACIO){
			live=false;
		}else if (!muted) {
			MensajeLog * mjeLog = (MensajeLog*) mje;
			file << mjeLog->getHora() << " " << mjeLog->getPid()<< " " << mjeLog->getId() << ": "
					<< mjeLog->getMensaje() << std::endl;
		}
		delete mje;
}

void LoggerListener::mute() {
	muted = 1;
}
void LoggerListener::resume() {
	muted = 0;
}

