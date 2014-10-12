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
 * Permite tener una comunicacion sincronica doble via (con 2 fifos) entre dos procesos.
 */
class ViaDoble {

private:
	bool duenio;
	bool abierta;
	Serializador serializador;
	FifoEscritura out;
	FifoLectura in;
	FifoEscritura inEsc;


	void abrir();
	void cerrar();
public:

	/**
	 * Nombre: el nombre de la cola
	 * Duenio: Si es el duenio de la via, esto implicara que busque eliminarla al finalizar y use o no las vias invertidas.
	 */
	ViaDoble(const string nombre, bool duenio);
	~ViaDoble();
	void enviar(Mensaje * mje);
	Mensaje * recibir();

	/**
	 * Retorna el nombre del archivo de entrada..
	 */
	string getNombreEntrada();
};

#endif /* VIADOBLE_H_ */
