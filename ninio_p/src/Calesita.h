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


class Calesita {
public:
	Calesita();
	int entrar(std::string boleto);//devuelve CALESITA_PASAR si pudo entrar CALESITA_NO_PASAR sino
	virtual ~Calesita();

	//terminar de implementar
	int sentarse(int lugar);//devuelve en el lugar que se sento

private:
	LockFile entrada;
	LockFile asientos;
	LockFile salida;
	Serializador ser;
	FifoEscritura fifoEsc;
	FifoLectura fifoLec;

};

#endif /* CALESITA_H_ */
