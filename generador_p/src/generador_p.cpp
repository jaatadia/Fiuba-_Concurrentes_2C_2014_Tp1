//============================================================================
// Name        : generador_p.cpp
// Author      : Jonathan
// Version     :
// Description : Proceso para generar porocesos ninio cada cierto tiempo
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "src/logger/Logger.h"
#include "src/constantes.h"
#include "src/proceso/Proceso.h"
using namespace std;

/**
 * Recibe como parametros 0 y 1: el nombre del ejecutable y la cantidad de ninios.
 */
int main(int argc, char * argv []) {
	int tiempoMax = 5;
	int cantNinios = atoi(argv[1]);

	if(argc > 2){
		//TODO CARGAR DE PARAMETROS LA CANT DE NINIOS.
	}

	Logger log("GENERADOR");
	log.log("Iniciado: se crearan <0> ninios",1,cantNinios);
	//TODO NO SE ESTAN GUARDANDO REFERENCIAS A LOS NINIOS. HAY QUE PENSAR MEJOR ESTO.
	for(int i = 0; i < cantNinios; i++){
		//creo un ninio cada tiempo random.
		sleep(rand()% tiempoMax);
		Proceso ninio(EJECUTABLE_NINIO);
		log.log("Se crea ninio con pid <0>", 1, ninio.getPid());
	}

	for(int i = 0; i < cantNinios; i++){
		pid_t pid = wait(NULL);
		log.log("Termino el ninio con pid <0>", 1, pid);
	}
}
