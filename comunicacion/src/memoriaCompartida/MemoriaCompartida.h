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


#endif /* MEMORIACOMPARTIDA_H_ */

