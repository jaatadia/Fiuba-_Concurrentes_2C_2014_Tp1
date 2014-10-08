/*
 * Semaforo.cpp
 *
 *  Created on: Oct 8, 2014
 *      Author: javier
 */

# include "Semaforo.h"
Semaforo::Semaforo (const char * nombre,int valorInicial ) {
	this->valorInicial = valorInicial ;
	key_t clave = ftok(nombre,'a');
	this-> id = semget ( clave ,1 ,0666 | IPC_CREAT ) ;
}

Semaforo::~Semaforo () {
}

int Semaforo::inicializar () {
	union semnum {
		int val ;
		struct semid_ds * buf ;
		ushort * array ;
	};
	semnum init ;
	init.val = this->valorInicial ;
	int resultado = semctl ( this->id ,0 , SETVAL , init ) ;
	return resultado ;
}



int Semaforo::wait () {
	return wait_cant(1);
}

int Semaforo::signal () {
	return signal_cant(1);
}

int Semaforo::wait_cant (int cant) {
	struct sembuf operacion ;
	operacion.sem_num = 0; // numero de s e m a f o r o
	operacion.sem_op = -cant; // restar cant al s e m a f o r o
	operacion.sem_flg = SEM_UNDO ;
	int resultado = semop ( this-> id ,&operacion ,1 ) ;
	return resultado ;
}

int Semaforo::signal_cant (int cant) {
	struct sembuf operacion ;
	operacion.sem_num = 0; // numero de s e m a f o r o
	operacion.sem_op = cant; // sumar cant al s e m a f o r o
	operacion.sem_flg = SEM_UNDO ;
	int resultado = semop ( this-> id ,&operacion ,1 ) ;
	return resultado ;
}

void Semaforo :: eliminar () {
	semctl ( this->id ,0 , IPC_RMID ) ;
}
