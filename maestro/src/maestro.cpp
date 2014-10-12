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
#include "src/seniales/SignalHandler.h"
#include <list>
using namespace std;


int calcular_random(int min,int max){
	srand(time(NULL));
	int resultado = rand()%(max-min+1);
	return resultado+min;
}

void bloquearSenialFallo(){

}
/*PARAMETROS:
 * 0 el nombre del programa
 * 1 duracion de la vuelta
 * 2 precio del boleto
 * 3 cantidad de lugares de la calestia
 * 4 si hay 4 entonces no debugg TODO ES MAS PROLIJO QUE RECIBA ALGO CONCRETO.
 */
int main(int argc, char* argv[]) {
	//TODO SI FALLA ALGUNO HAY Q MATAR EL RESTO DE LOS PROCESOS.

	int duracionVuelta = 10;
	int precioBoleto = 1;
	int cantidadAsientos = 3;
	list<int> pids;
	if(argc >= 4){
		duracionVuelta=atoi(argv[1]);
		precioBoleto=atoi(argv[2]);
		cantidadAsientos=atoi(argv[3]);
	}
	GracefullQuitter * quitter = Proceso::getErrorFlag();

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
		pids.push_back(logger.getPid());
		//---------------INICIALIZANDO GENERADOR DE NINIOS--------------------
		Parametros paramsGen;
		paramsGen.push(calcular_random(MIN_NINIOS,MAX_NINIOS));
		paramsGen.push(cantidadAsientos);
		Proceso generador(EJECUTABLE_GENERADOR,paramsGen,&log);
		log.log("Iniciado proceso del GENERADOR con PID <0>",1, generador.getPid());
		pids.push_back(generador.getPid());

		//---------------INICIALIZANDO CAJERO--------------------
		Parametros paramsCajero;
		paramsCajero.push(precioBoleto);
		Proceso cajero(EJECUTABLE_CAJERO,paramsCajero,&log);
		log.log("Iniciado proceso del CAJERO con PID <0>",1, cajero.getPid());
		pids.push_back(cajero.getPid());

		//---------------INICIALIZANDO CALESITA--------------------
		Parametros paramsCalesita;
		paramsCalesita.push(cantidadAsientos);
		paramsCalesita.push(duracionVuelta);
		Proceso calesita(EJECUTABLE_CALESITA,paramsCalesita,&log);
		log.log("Iniciado proceso del CALESITA con PID <0>",1, calesita.getPid());
		pids.push_back(calesita.getPid());
		//---------------INICIALIZANDO ADMINISTRADOR--------------------
		Proceso admin(EJECUTABLE_ADMINISTRADOR,&log);
		log.log("Iniciado proceso del ADMINISTRADOR con PID <0>",1, admin.getPid());
		pids.push_back(admin.getPid());

		if(!quitter->alive()){
			cout<<"Error inicializando los procesos, se finaliza la simulacion" << endl;
			kill(QUIT_SIGNAL,generador.getPid());
		}
		waitpid(generador.getPid(),NULL,0);

		kill(QUIT_SIGNAL,cajero.getPid());
		waitpid(cajero.getPid(),NULL,0);
		kill(QUIT_SIGNAL,calesita.getPid());
		waitpid(calesita.getPid(),NULL,0);
		kill(QUIT_SIGNAL,admin.getPid());
		waitpid(admin.getPid(),NULL,0);
		kill(QUIT_SIGNAL,logger.getPid());

	} catch (ProcesoException & e) {
		std::cout<<"La simulacion no pudo comenzar. No se pudideron correr todos los procesos: "<<e.what()<<endl;
		list<int>::iterator it;
		for(it= pids.begin(); it != pids.end(); ++it){
			kill(QUIT_SIGNAL,*it);
		}
	}
	delete quitter;
	SignalHandler::destruir();
}
