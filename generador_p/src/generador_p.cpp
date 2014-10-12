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

#include "src/proceso/Parametros.h"
#include "src/logger/Logger.h"
#include "src/constantes.h"
#include "src/proceso/Proceso.h"
#include "src/seniales/SignalHandler.h"
using namespace std;

/**
 * Recibe como parametros 0 y 1: el nombre del ejecutable y la cantidad de ninios.
 * y 2 la cantidad de asientos
 */
int main(int argc, char * argv []) {
	int tiempoMax = 5;
	int cantNinios = atoi(argv[1]);
	int asientos = atoi (argv[2]);

	if(argc > 2){
		//TODO CARGAR DE PARAMETROS LA CANT DE NINIOS.
	}

	Logger log("GENERADOR");
	log.log("Iniciado: se crearan <0> ninios",1,cantNinios);
	//TODO NO SE ESTAN GUARDANDO REFERENCIAS A LOS NINIOS. HAY QUE PENSAR MEJOR ESTO.
	GracefullQuitter grace;
	SignalHandler::getInstance()->registrarHandler(QUIT_SIGNAL, &grace);
	for(int i = 0; i < cantNinios && grace.alive(); i++){
		Parametros params;
		params.push(i);
		params.push(asientos);
		//creo un ninio cada tiempo random.
		sleep((rand()% tiempoMax) + 1);
		Proceso ninio(EJECUTABLE_NINIO,params, &log);
		log.log("Se crea ninio con pid <0>", 1, ninio.getPid());
	}

	for(int i = 0; i < cantNinios; i++){
		pid_t pid = wait(NULL);
		log.log("Termino el ninio con pid <0>", 1, pid);
	}
	SignalHandler::destruir();
}
