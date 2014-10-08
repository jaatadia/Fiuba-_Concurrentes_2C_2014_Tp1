/*
 * MemoriaCompartida.cpp
 *
 *  Created on: Oct 7, 2014
 */

#include "MemoriaCompartida.h"

using namespace std;


template <class T> MemoriaCompartida<T>::MemoriaCompartida():shmId(0),ptrDatos(NULL) {
}

template <class T> MemoriaCompartida<T>::MemoriaCompartida( const string &archivo,const char letra ):shmId(0),ptrDatos(NULL) {
	key_t clave = ftok( archivo.c_str(),letra );

	if ( clave > 0 ) {

		this->shmId = shmget( clave,sizeof(T),0644|IPC_CREAT );
		if ( this->shmId > 0 ) {

			void* tmpPtr = shmat( this->shmId,NULL,0 );

			if ( tmpPtr != (void*) -1 ) {
				this->ptrDatos = static_cast<T*> (tmpPtr);
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


