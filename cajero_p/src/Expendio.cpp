/*
 * Expendio.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "Expendio.h"
#include "src/constantes.h"
#include "src/fifo/ViaDoble.h"
#include <iostream>
#include "src/transferencia/MensajeCompraBoleto.h"
using namespace std;


Expendio::Expendio(int precio):precio(precio) {

	this->com =new ViaDoble(PATH_FIFOVENTA,true);

	fifoEsc = NULL;
}

Expendio::~Expendio() {
	if(fifoEsc != NULL){
		fifoEsc->cerrar();
		delete fifoEsc;
	}
	delete this->com;

}

int Expendio::recibirNinio() {
	//Si todavia no tengo la fifo que mantenga viva la conexion, la creo y la abro..

	com->abrir();
	if(fifoEsc == NULL){
		Serializador * ser = this->com->getSerializador();
		fifoEsc = new FifoEscritura(this->com->getNombreEntrada(), *ser );
		fifoEsc->abrir();
	}
	Mensaje* mje = (Mensaje*)com->recibir();
	MensajeCompraBoleto* mjeb = (MensajeCompraBoleto *) mje;
	int importe = mjeb->getImporte();
	delete mje;
	return importe;
}

void Expendio::darBoleto(int nroTicket) {
	MensajeCompraBoleto* mensaje = new MensajeCompraBoleto(this->precio);
	mensaje->setNroBoleto(nroTicket);
	com->enviar(mensaje);
	com->cerrar();
}

void Expendio::rechazarPagoInsuficiente() {
	//setea el importe que sale el ticket y un nro de ticket invalido
	MensajeCompraBoleto* mensaje = new MensajeCompraBoleto(this->precio);
	mensaje->setNroBoleto(NRO_BOLETO_INVALIDO);
	com->enviar(mensaje);
	com->cerrar();

}
