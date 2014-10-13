/*
 * Asientos.h
 *
 *  Created on: Oct 12, 2014
 *      Author: florencia
 */

/*
 * Maneja la memoria compartida (array) de los asientos de la calesita.
 * El array de asientos va de 0 a cantidad_asientos
 * En caso de errores tira MemoriaCompartidaExcepction
 */

#ifndef ASIENTOS_H_
#define ASIENTOS_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#include "../constantes.h"
#include "MemoriaCompartidaException.h"

class Asientos {

private:
	int	shmId;
	int* ptrDatos;
	int cantAsientos;

	int	cantidadProcesosAtachados() const;

public:
	Asientos(int cantidad_asientos); //Crea el segmento y/o se attacha
	~Asientos(); //Se desatacha y si no hay mas procesos atachados destruye el segmento
	int estaOcupado(int nro_asiento); //Devuelve 1 si está ocupado nro_asiento, 0 si esta libre
	int sentarme(int nro_asiento); //devuelve -1 si no se pudo sentar en nro_asiento
	void levantarme(int nro_asiento);
	int getCantidadAsientos(); //devuelve la cantidad de asientos de la calesita
	/* const string getTipo(int nro_asiento); //Devuelve en sring el tipo de juguete de la calesita */
};

#endif /* ASIENTOS_H_ */
