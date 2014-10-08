/*
 * entrada.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Entrada.h"

Entrada::Entrada(int numero) : error(0), ninos(0), nroNinosPorVuelta(numero),nroNinosEnVuelta(0), ser(),fifoLec(PATH_FIFO_CALESITA_HACIA_CALESITA,ser),fifoLecEsc(PATH_FIFO_CALESITA_HACIA_CALESITA,ser),fifoEsc(PATH_FIFO_CALESITA_HACIA_NINOS,ser),fifoTimeout(PATH_FIFO_CALESITA_TIMEOUT,ser){
	fifoLec.abrir();
	fifoLecEsc.abrir();
	fifoEsc.abrir();
	fifoTimeout.abrir();
}

Mensaje* Entrada::getBoleto(){
	ninos++;
	int found = 0;
	Mensaje* resultado = NULL;
	fifoTimeout.escribir(new MensajeInt(ninos));//aviso que voy a leer al que me corta por timeout
	while(found == 0){
		Mensaje* msg = fifoLec.leer(); //espero al niño
		if(msg->getTipo()==MENSAJE_NUMERO){//me fijo si es el timeout de un nino
			MensajeInt* msgInt = static_cast<MensajeInt*>(msg);
			if(msgInt->getInt()==ninos) {//me fijo si es el timeout del nino actual
				found = 1;
				resultado = 0;
			}
		}else if(msg->getTipo()==MENSAJE_VACIO){//me fijo si no hubo un error
			found = 1;
			resultado = NULL;
			error = 1;
		}else{//sino, fue un nino bien
			found = 1;
			resultado = NULL;
		}
	}
	return resultado;
}

int Entrada::verificarBoleto(Mensaje* msj){
	if(true){// falta verificar validez del boleto
		fifoEsc.escribir(new MensajeInt(CALESITA_PASAR));
		return 1;//siempre es valido por ahora
	}else{
		fifoEsc.escribir(new MensajeInt(CALESITA_NO_PASAR));
		return -1;//siempre es valido por ahora
	}
}


void Entrada::esperarSentado(){
	int found = 0;
	while(found == 0){
		Mensaje* msg = fifoLec.leer(); //espero al niño
		if(msg->getTipo()==MENSAJE_NUMERO){//me fijo si es el timeout de un nino
		}else if(msg->getTipo()==MENSAJE_VACIO){//me fijo si no hubo un error
			error = 1;
			found = 1;
		}else{//sino, fue un nino bien
			found = 1;
		}
	}
}

int Entrada::tramitarNino(Mensaje* msj){
	if(verificarBoleto(msj)==1){
		//esperarSentado();
		nroNinosEnVuelta++;
	}
	delete msj;
	return 1;
}

int Entrada::inicial(){
	Mensaje* msj;
	while((msj = getBoleto())==NULL){
		if (huboError()) return -1;
	}
	return tramitarNino(msj);
}

int Entrada::proximo(){
	Mensaje* msj = getBoleto();
	if (msj == NULL) {
		return ((huboError())? -1:0);
	}
	return tramitarNino(msj);
}


void Entrada::reset(){
	error=0;
	nroNinosEnVuelta=0;
	//tomar semaforos
}

void Entrada::liberar(){
	//liberar semaforo
}

int Entrada::huboError(){
	return error==1;
}

int Entrada::proxNino(){
	if(nroNinosEnVuelta==0) return inicial();
	else if(nroNinosEnVuelta<nroNinosPorVuelta) return proximo();
	else return -1;
}

Entrada::~Entrada() {
	fifoLec.cerrar();
	fifoLecEsc.cerrar();
	fifoEsc.cerrar();
	fifoTimeout.cerrar();
	fifoLec.eliminar();
	fifoEsc.eliminar();
}
