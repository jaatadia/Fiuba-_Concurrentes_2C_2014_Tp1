/*
 * Asientos.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: florencia
 */

#include "Asientos.h"

Asientos::Asientos(int cant_asientos): shmId(0),ptrDatos(NULL),cantAsientos(cant_asientos) {

	key_t clave = ftok( MEMCOMP_ASIENTOS_ARCH.c_str(),MEMCOMP_ASIENTOS_LETRA );

	if ( clave > 0 ) {

		this->shmId = shmget( clave,sizeof(int)*cant_asientos,0777|IPC_CREAT );
		if ( this->shmId > 0 ) {

			void* tmpPtr = shmat( this->shmId,NULL,0 );

			if ( tmpPtr != (void*) -1 ) {
				this->ptrDatos = static_cast<int*> (tmpPtr);
			} else {
				throw MemoriaCompartidaException("Error en shmat(), el segmento creado no se mapeo al proceso",strerror(errno));
			}
		} else {
			throw MemoriaCompartidaException("Error en shmget(), no se creara el segmento",strerror(errno));
		}
	} else {
		throw MemoriaCompartidaException("Error en ftok(), no se creara el segmento",strerror(errno));
	}
}

Asientos::~Asientos() {
	int errorDt = shmdt( static_cast<void*> (this->ptrDatos) );

		if ( errorDt != -1 ) {
			int procAtachados = this->cantidadProcesosAtachados();
			if ( procAtachados == 0 ) {
				int errorDest = shmctl( this->shmId,IPC_RMID,NULL );
				if ( errorDest == -1) throw MemoriaCompartidaException("Error en shmctl() (destruccion de la memoria)",strerror(errno));
			}
		} else {
			throw MemoriaCompartidaException("Error en shmdt() y no se eliminará",strerror(errno));
		}
	}

int	Asientos::cantidadProcesosAtachados() const {
	shmid_ds estado;
	int errorEst = shmctl( this->shmId,IPC_STAT,&estado );
	if (errorEst == -1) throw MemoriaCompartidaException("Error en shmctl() al obtener cantidad de procesos attached",strerror(errno));
	return estado.shm_nattch;
}

int Asientos::estaOcupado(int nro_asiento){
	return (this->ptrDatos[nro_asiento]);
}

int Asientos::sentarme(int nro_asiento){
	if ( (this->ptrDatos[nro_asiento]) == 0 ){
		(this->ptrDatos[nro_asiento]) = 1;
		return 0;
	} else return -1;
}

void Asientos::levantarme(int nro_asiento){
	this->ptrDatos[nro_asiento] = 0;

}

int Asientos::getCantidadAsientos(){
	return this->cantAsientos;
}

