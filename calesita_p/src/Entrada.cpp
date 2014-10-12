/*
 * entrada.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Entrada.h"

Entrada::Entrada(int numero, int vuelta, Logger* log, GracefullQuitter* quitter) : error(0), vuelta(vuelta), ninos(0), nroNinosPorVuelta(numero),nroNinosEnVuelta(0), ser(),fifoLec(PATH_FIFO_CALESITA_HACIA_CALESITA,ser),fifoLecEsc(PATH_FIFO_CALESITA_HACIA_CALESITA,ser),fifoEsc(PATH_FIFO_CALESITA_HACIA_NINOS,ser),fifoTimeout(PATH_FIFO_CALESITA_TIMEOUT,ser), log(log),semAsientosOcupados(PATH_ARCH_SEM_ASIENTOS.c_str(),0),semSoltarNinos(PATH_ARCH_SEM_CALE.c_str(),0),quitter(quitter){
	fifoLec.abrir();
	fifoLecEsc.abrir();
	fifoEsc.abrir();
	fifoTimeout.abrir();
	semAsientosOcupados.inicializar();
	semSoltarNinos.inicializar();
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
				log->log("No han llegado niños");
				found = 1;
				delete(msg);
				resultado = NULL;
			}
		}else if(msg->getTipo()==MENSAJE_VACIO){//me fijo si no hubo un error
			error = 1;
			found = 1;
			delete(msg);
			resultado = NULL;
		}else{//sino, fue un nino bien
			log->log("Ha llegado un niño");
			found = 1;
			resultado = msg;
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
		return -1;
	}
}


int Entrada::tramitarNino(Mensaje* msj){
	log->log("Verificando el boleto del niño");
	if(verificarBoleto(msj)==1){
		log->log("El boleto es valido");
		nroNinosEnVuelta++;
	}else{
		log->log("El boleto Es invalido");
	}
	delete msj;
	return 1;
}

int Entrada::inicial(){
	log->log("Esperando al primer niño");
	Mensaje* msj;
	while((msj = getBoleto())==NULL){
		if (huboError() || (!quitter->alive())){
			throw Exception("Se debe cerrar el programa","No hay mas ninio");
		}
	}
	return tramitarNino(msj);
}

int Entrada::proximo(){
	log->log("Esperando al proximo niño");
	Mensaje* msj = getBoleto();
	if (msj == NULL) {
		return ((huboError())? -1:0);
	}
	return tramitarNino(msj);
}


void Entrada::reset(){
	semAsientosOcupados.wait_cant(nroNinosEnVuelta);//espero que lo ninios salgan
	error=0;
	nroNinosEnVuelta=0;
}

void Entrada::liberar(){
	semSoltarNinos.signal_cant(nroNinosEnVuelta);
}

int Entrada::huboError(){
	return error==1;
}

void Entrada::esperarSienten(){
	semAsientosOcupados.wait_cant(nroNinosEnVuelta);
}

void Entrada::comenzarVuelta(){
	sleep(vuelta);
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
	fifoTimeout.eliminar();
	semAsientosOcupados.eliminar();
	semSoltarNinos.eliminar();
}

