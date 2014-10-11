//============================================================================
// Name        : maestro.cpp
// Author      : jtierno
// Version     :
// Description : Proceso que genera el resto de los procesos.
//============================================================================

#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "src/constantes.h"
#include "src/proceso/Proceso.h"
#include "src/proceso/ProcesoException.h"
#include "src/logger/Logger.h"
#include "src/proceso/Parametros.h"
using namespace std;


int calcular_random(int min,int max){
	srand(time(NULL));
	int resultado = rand()%(max-min+1);
	return resultado+min;
}

//recibe como 0 el nombre del programa
// 1 duracion de la vuelta
// 2 precio del boleto
// 3 cantidad de lugares de la calestia
// 4 si hay 4 entonces no debugg
int main(int argc, char* argv[]) {
	//TODO SI FALLA ALGUNO HAY Q MATAR EL RESTO DE LOS PROCESOS.

	int duracionVuelta = 10;
	int precioBoleto = 1;
	int cantidadAsientos = 3;
	if(argc >= 4){
		duracionVuelta=atoi(argv[1]);
		precioBoleto=atoi(argv[2]);
		cantidadAsientos=atoi(argv[3]);
	}


	try {

		//---------------INICIALIZANDO LOGGER--------------------
		Parametros paramsLogger;
		if(argc != 5){
			paramsLogger.push("-d");
			paramsLogger.push(DEFAULT_LOG_FILE);
		}
		Proceso logger(EJECUTABLE_LOGGER,paramsLogger);
		Logger log("MAESTRO");
		log.log("Iniciado proceso del LOGGER con PID <0>",1, logger.getPid());

		//---------------INICIALIZANDO GENERADOR DE NINIOS--------------------
		Parametros paramsGen;
		paramsGen.push(calcular_random(MIN_NINIOS,MAX_NINIOS));
		paramsGen.push(cantidadAsientos);
		Proceso generador(EJECUTABLE_GENERADOR,paramsGen);
		log.log("Iniciado proceso del GENERADOR con PID <0>",1, generador.getPid());


		//---------------INICIALIZANDO CAJERO--------------------
		Parametros paramsCajero;
		paramsCajero.push(precioBoleto);
		Proceso cajero(EJECUTABLE_CAJERO,paramsCajero);
		log.log("Iniciado proceso del CAJERO con PID <0>",1, cajero.getPid());

		//---------------INICIALIZANDO CALESITA--------------------
		Parametros paramsCalesita;
		paramsCalesita.push(cantidadAsientos);
		paramsCalesita.push(duracionVuelta);
		Proceso calesita(EJECUTABLE_CALESITA,paramsCalesita);
		log.log("Iniciado proceso del CALESITA con PID <0>",1, calesita.getPid());

		//---------------INICIALIZANDO ADMINISTRADOR--------------------
		Proceso admin(EJECUTABLE_ADMINISTRADOR);
		log.log("Iniciado proceso del CALESITA con PID <0>",1, admin.getPid());

		waitpid(generador.getPid(),NULL,0);

		kill(SIGUSR1,cajero.getPid());
		waitpid(cajero.getPid(),NULL,0);
		kill(SIGUSR1,calesita.getPid());
		waitpid(calesita.getPid(),NULL,0);
		kill(SIGUSR1,admin.getPid());
		waitpid(admin.getPid(),NULL,0);

		kill(SIGUSR1,logger.getPid());
	} catch (ProcesoException & e) {
		std::cout<<"Fallo del maestro"<<e.getMensaje()<<endl;
	}

}
