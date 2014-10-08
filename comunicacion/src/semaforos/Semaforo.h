/*
 * Semaforo.h
 *
 *  Created on: Oct 8, 2014
 *      Author: javier
 */

#ifndef SEMAFORO_H_
#define SEMAFORO_H_
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
class Semaforo {
private:
	int id ;
	int valorInicial ;


public:
	Semaforo (const char * nombre,int valorInicial);
	int inicializar();//solo el que lo crea deberia llamar a esto
	virtual ~ Semaforo () ;
	int wait(); //decrementa
	int signal(); //incrementa

	int wait_cant(int cant); //decrementa en cant
	int signal_cant(int cant); //incrementa en cant

	void eliminar();//solo el que lo crea deberia llamar a esto
};
# endif /*SEMAFORO_H_*/
