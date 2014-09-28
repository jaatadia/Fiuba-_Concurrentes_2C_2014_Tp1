/*
 * ViaDoble.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef VIADOBLE_H_
#define VIADOBLE_H_
#include "FifoEscritura.h"
#include "FifoLectura.h"
#include <string>
#include "../transferencia/Mensaje.h"
#include "../transferencia/Serializador.h"
using namespace std;

static const string IN_POSTFIX = "in";
static const string OUT_POSTFIX = "out";

/**
 * Permite tener una comunicacion sincronica doble via entre dos procesos.
 * Para que pueda funcionar, inPrimero deberia ir invertido en cada proceso.
 */
class ViaDoble {

private:
	FifoEscritura * out;
	FifoLectura * in;
	Serializador * ser;
	bool duenio;
public:
	/**
	 *
	 * nombre: el nombre de la cola
	 * inlock: si requiere lock la entrada
	 * outlock: si requiere lock la salida
	 * inPrimero: si debe abrir primero la entrada.
	 */
	ViaDoble(const string nombre, const bool inlock, const bool outlock, bool inPrimero);
	~ViaDoble();
	void enviar(Mensaje * mje);
	Mensaje * recibir();
	bool isDuenio() const;
	void setDuenio(bool duenio);
};

#endif /* VIADOBLE_H_ */
