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
 */
class ViaDoble {

private:
	FifoEscritura * out;
	FifoLectura * in;
	Serializador * serializador;
	bool duenio;
	bool abierta;
public:

	//TODO SACAR EL PARAMETRO INVERSA Y DEJAR SOLAMENTE SI ES EL DUENIO O NO.
	/**
	 *
	 * Nombre: el nombre de la cola
	 * Duenio: Si es el duenio de la via, esto implicara que busque eliminarla al finalizar.
	 */
	ViaDoble(const string nombre, bool duenio);
	~ViaDoble();
	void enviar(Mensaje * mje);
	Mensaje * recibir();
	void cerrar();
	void abrir();
	/**
	 * Retorna el nombre del archivo de entrada..
	 */
	string getNombreEntrada();
	Serializador* getSerializador() const;
};

#endif /* VIADOBLE_H_ */
