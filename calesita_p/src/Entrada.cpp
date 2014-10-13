/*
 * entrada.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#include "Entrada.h"

Entrada::Entrada(int numero, int vuelta, Logger* log, GracefullQuitter* quitter) : error(0), vuelta(vuelta), ninos(0), nroNinosPorVuelta(numero),nroNinosEnVuelta(0), ser(),fifoLec(PATH_FIFO_CALESITA_HACIA_CALESITA,ser),fifoLecEsc(PATH_FIFO_CALESITA_HACIA_CALESITA,ser),fifoEsc(PATH_FIFO_CALESITA_HACIA_NINOS,ser),log(log),semAsientosOcupados(PATH_ARCH_SEM_ASIENTOS.c_str(),0),semSoltarNinos(PATH_ARCH_SEM_CALE.c_str(),0),quitter(quitter){
	fifoLec.abrir();
	fifoLecEsc.abrir();
	fifoEsc.abrir();
	semAsientosOcupados.inicializar();
	semSoltarNinos.inicializar();
	log->log("ninios maximos por vuelta <0>",1,nroNinosPorVuelta);
}

Mensaje* Entrada::getBoleto(){
	ninos++;
	Mensaje* msg = fifoLec.leer(); //espero al niño
	log->log("Ha llegado un niño con boleto: "+msg->serializar());
	return msg;
}

int Entrada::verificarBoleto(Mensaje* msj){
	return 1;
}


int Entrada::tramitarNino(Mensaje* msj){
	log->log("Verificando el boleto del niño");
	if(verificarBoleto(msj)==1){
		log->log("El boleto "+msj->serializar()+" es valido");
		fifoEsc.escribir(new MensajeInt(CALESITA_PASAR));
		nroNinosEnVuelta++;
	}else{
		log->log("El boleto "+msj->serializar()+"  Es invalido");
		fifoEsc.escribir(new MensajeInt(CALESITA_NO_PASAR));
	}
	delete msj;
	return 1;
}


int Entrada::proximo(){
	log->log("Esperando al proximo niño");
	Mensaje* msj = getBoleto();
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
	log->log("Comenzando vuelta de <0> segundos con <1> ninios",2,vuelta,nroNinosEnVuelta);
	sleep(vuelta);
}

bool Entrada::estaVacia(){
	return (nroNinosEnVuelta==0);
}

bool Entrada::estaLlena(){
	return (nroNinosEnVuelta==nroNinosPorVuelta);
}

Entrada::~Entrada() {
	fifoLec.cerrar();
	fifoLecEsc.cerrar();
	fifoEsc.cerrar();
	fifoLec.eliminar();
	fifoEsc.eliminar();
	semAsientosOcupados.eliminar();
	semSoltarNinos.eliminar();
}

