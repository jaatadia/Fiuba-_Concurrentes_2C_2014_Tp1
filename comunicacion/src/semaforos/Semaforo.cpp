/*
 * Semaforo.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: javier
 */

#include <string.h>
#include "../Exception.h"
#include <errno.h>

# include "Semaforo.h"
Semaforo::Semaforo (const char * nombre,int valorInicial ) {
	this->valorInicial = valorInicial ;
	key_t clave = ftok(nombre,'a');
	this-> id = semget ( clave ,1 ,0666 | IPC_CREAT ) ;
	if (id == -1){
		throw Exception("No se pudo abrir el semaforo", strerror(errno));
	}
}

Semaforo::~Semaforo () {
}

void Semaforo::inicializar () {
	union semnum {
		int val ;
		struct semid_ds * buf ;
		ushort * array ;
	};
	semnum init ;
	init.val = this->valorInicial ;
	int resultado = semctl ( this->id ,0 , SETVAL , init ) ;
	if (resultado == -1){
		throw Exception("No se pudo inicializar el semaforo", strerror(errno));
	}
}



void Semaforo::wait () {
	wait_cant(1);
}

void Semaforo::signal () {
	signal_cant(1);
}

void Semaforo::wait_cant (int cant) {
	struct sembuf operacion ;
	operacion.sem_num = 0; // numero de s e m a f o r o
	operacion.sem_op = -cant; // restar cant al s e m a f o r o
	operacion.sem_flg = 0 ;
	int resultado = semop ( this-> id ,&operacion ,1 ) ;
	if (resultado == -1){
		throw Exception("Se produjo un error al esperar por el semaforo", strerror(errno));
	}
}

void Semaforo::signal_cant (int cant) {
	struct sembuf operacion ;
	operacion.sem_num = 0; // numero de s e m a f o r o
	operacion.sem_op = cant; // sumar cant al s e m a f o r o
	operacion.sem_flg = 0 ;
	int resultado = semop ( this-> id ,&operacion ,1 ) ;
	if (resultado == -1){
		throw Exception("Se produjo un error al avisar al semaforo", strerror(errno));
	}
}

void Semaforo :: eliminar () {
	semctl ( this->id ,0 , IPC_RMID ) ;
}
