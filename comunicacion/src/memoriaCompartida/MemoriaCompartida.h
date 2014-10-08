/*
 * MemoriaCompartida.h
 *
 *  Created on: Oct 7, 2014
 */

#ifndef MEMORIACOMPARTIDA_H_
#define MEMORIACOMPARTIDA_H_

#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include "MemoriaCompartidaException.h"

using namespace std;

template <class T> class MemoriaCompartida {

	private:
		int	shmId;
		T*	ptrDatos;

		int	cantidadProcesosAdosados() const;

	public:
		MemoriaCompartida();
		~MemoriaCompartida();

		MemoriaCompartida( const string &archivo,const char letra );
		MemoriaCompartida( const MemoriaCompartida &origen );
		MemoriaCompartida<T>& operator= ( const MemoriaCompartida &origen );

		/*
		void crear( const string &archivo,const char letra );
		void liberar();
		*/

		void escribir( const T &dato );
		T leer() const;
};



template <class T> MemoriaCompartida<T>::MemoriaCompartida():shmId(0),ptrDatos(NULL) {
}

template <class T> MemoriaCompartida<T>::MemoriaCompartida( const string &archivo,const char letra ):shmId(0),ptrDatos(NULL) {
	key_t clave = ftok( archivo.c_str(),letra );

	if ( clave > 0 ) {

		this->shmId = shmget( clave,sizeof(T),0644|IPC_CREAT|IPC_EXCL ); //si ya existía no la crea!
		if ( this->shmId > 0 ) {

			void* tmpPtr = shmat( this->shmId,NULL,0 );

			if ( tmpPtr != (void*) -1 ) {
				this->ptrDatos = static_cast<T*> (tmpPtr);
			} else {
				throw MemoriaCompartidaException("Error en shmat(), el segmento creado no se mapeo al proceso",strerror(errno));
			}
		} else {
			if (errno == EEXIST) //TODO avisarle a la caja q no la inicialice en cero. como? nueva excepcion?¿?
				;
			else
				throw MemoriaCompartidaException("Error en shmget(), no se creara el segmento",strerror(errno));
		}
	} else {
		throw MemoriaCompartidaException("Error en ftok(), no se creara el segmento",strerror(errno));
	}
}

template <class T> MemoriaCompartida<T>::MemoriaCompartida( const MemoriaCompartida &origen ):shmId(origen.shmId) {
	void* tmpPtr = shmat( origen.shmId,NULL,0 );

	if ( tmpPtr != (void*) -1 ) {
		this->ptrDatos = static_cast<T*> (tmpPtr);
	} else {
		throw MemoriaCompartidaException("Error en shmat(), el segmento creado no se mapeo al proceso",strerror(errno));
	}
}

template <class T> MemoriaCompartida<T>::~MemoriaCompartida() {
	int errorDt = shmdt ( static_cast<void*> (this->ptrDatos) );

	if ( errorDt != -1 ) {
		int procAdosados = this->cantidadProcesosAdosados ();
		if ( procAdosados == 0 ) {
			int errorDest = shmctl( this->shmId,IPC_RMID,NULL );
			if ( errorDest == -1) throw MemoriaCompartidaException("Error en shmctl() (destruccion de la memoria)",strerror(errno));
		}
	} else {
		throw MemoriaCompartidaException("Error en shmdt() y no se eliminara",strerror(errno));
	}
}

template <class T> MemoriaCompartida<T>& MemoriaCompartida<T>::operator= ( const MemoriaCompartida& origen ) {
	this->shmId = origen.shmId;
	void* tmpPtr = shmat( this->shmId,NULL,0 );

	if ( tmpPtr != (void*) -1 ) {
		this->ptrDatos = static_cast<T*> (tmpPtr);
	} else {
		throw MemoriaCompartidaException("Error en shmat(), no se pudo asignar la memoria",strerror(errno));
	}
	return *this;
}

/*
template <class T> void MemoriaCompartida<T>::crear( const string& archivo,const char letra ) {
	key_t clave = ftok ( archivo.c_str(),letra );

	if ( clave > 0 ) {
		this->shmId = shmget ( clave,sizeof(T),0644|IPC_CREAT );

		if ( this->shmId > 0 ) {
			void* tmpPtr = shmat ( this->shmId,NULL,0 );
			if ( tmpPtr != (void*) -1 ) {
				this->ptrDatos = static_cast<T*> (tmpPtr);
			} else {
				string mensaje = string("Error en shmat(): ") + string(strerror(errno));
				throw mensaje;
			}
		} else {
			string mensaje = string("Error en shmget(): ") + string(strerror(errno));
			throw mensaje;
		}
	} else {
		string mensaje = string("Error en ftok(): ") + string(strerror(errno));
		throw mensaje;
	}
}

template <class T> void MemoriaCompartida<T>::liberar() {
	int errorDt = shmdt ( (void *) this->ptrDatos );

	if ( errorDt != -1 ) {
		int procAdosados = this->cantidadProcesosAdosados ();
		if ( procAdosados == 0 ) {
			shmctl ( this->shmId,IPC_RMID,NULL );
		}
	} else {
		string mensaje = string("Error en shmdt(): ") + string(strerror(errno));
		throw mensaje;
	}
}
*/

template <class T> void MemoriaCompartida<T>::escribir( const T &dato ) {
	*(this->ptrDatos) = dato;
}

template <class T> T MemoriaCompartida<T>::leer() const {
	return *(this->ptrDatos);
}

template <class T> int MemoriaCompartida<T>::cantidadProcesosAdosados() const {
	shmid_ds estado;
	int errorEst = shmctl( this->shmId,IPC_STAT,&estado );
	if (errorEst == -1) throw MemoriaCompartidaException("Error en shmctl() al obtener cantidad de procesos attached",strerror(errno));
	return estado.shm_nattch;
}


#endif /* MEMORIACOMPARTIDA_H_ */

