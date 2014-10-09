/*
 * Calesita.h
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#ifndef CALESITA_H_
#define CALESITA_H_

#include "src/constantes.h"
#include "src/lock/LockFile.h"
#include "src/transferencia/Serializador.h"
#include "src/transferencia/MensajeString.h"
#include "src/transferencia/MensajeInt.h"
#include "src/fifo/FifoLectura.h"
#include "src/fifo/FifoEscritura.h"
#include "src/logger/Logger.h"
#include "src/semaforos/Semaforo.h"

class Calesita {
public:
	Calesita(Logger* log);
	int entrar(std::string boleto);//devuelve CALESITA_PASAR si pudo entrar CALESITA_NO_PASAR sino
/*TODO*/	int sentarse(int lugar);//devuelve en el lugar que se sento
	void esperar();
/*TODO*/	void salir();
	virtual ~Calesita();


private:
	LockFile entrada;
	LockFile asientos;
	LockFile salida;
	Serializador ser;
	FifoLectura fifoLec;
	FifoEscritura fifoEsc;
	Logger* log;
	Semaforo semAsientos;
	Semaforo semVuelta;

};

#endif /* CALESITA_H_ */
