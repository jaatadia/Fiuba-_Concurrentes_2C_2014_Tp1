//============================================================================
// Name        : maestro.cpp
// Author      : jtierno
// Version     :
// Description : Proceso que genera el resto de los procesos.
//============================================================================

#include <iostream>
#include <stdio.h>
#include <sys/wait.h>

#include "src/constantes.h"
#include "src/proceso/Proceso.h"
#include "src/proceso/ProcesoException.h"
#include "src/logger/Logger.h"
#include "src/proceso/Parametros.h"
using namespace std;

int main() {
	//TODO SI FALLA ALGUNO HAY Q MATAR EL RESTO DE LOS PROCESOS.
	try {
		Parametros paramsLogger;
		paramsLogger.push("-d");
		paramsLogger.push(DEFAULT_LOG_FILE);
		Proceso logger(EJECUTABLE_LOGGER,paramsLogger);
		Logger log("MAESTRO");

		log.log("Iniciado proceso del LOGGER con PID <0>",1, logger.getPid());
		Proceso cajero(EJECUTABLE_CAJERO);
		log.log("Iniciado proceso del CAJERO con PID <0>",1, cajero.getPid());
		Proceso generador(EJECUTABLE_GENERADOR);
		log.log("Iniciado proceso del GENERADOR con PID <0>",1, generador.getPid());
	} catch (ProcesoException & e) {


	}

}
