//Proceso que le pide al cajero la caja para chequear recaudacion
//Se comunica con el cajero mediante la Caja


/**
 * Recibe como parametros 0 y 1 el nombre del ejecutable y el pid del padre.
 */

#include <iostream>
#include <sstream>
#include <string>

#include <stdlib.h>
#include <unistd.h>

#include "src/seniales/SignalHandler.h"
#include "src/seniales/GracefullQuitter.h"

#include "src/Caja.h"
#include "src/Exception.h"
#include "src/InterrumpidoException.h"
#include "src/memoriaCompartida/MemoriaCompartidaException.h"
#include "src/logger/Logger.h"
#include "src/constantes.h"

using namespace std;

int calcularRandom () {
	srand ( time(NULL) );
	int resultado = rand() % MAX_T_RAND;
	return resultado+1;
}

int main(int argc, char* argv[]) {

	//Inicializo el quitter.
	GracefullQuitter grace;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &grace); //le paso como handler de la señal sigusr1

	try {
		Logger logger("ADMINISTRADOR");

		try{
			Caja caja;

			while (grace.alive()) {
				try {
					int segs = calcularRandom();
					logger.log("Me voy a dormir <0> segundos.",1,segs);
					sleep(segs);
					logger.log("Me desperté, quiero ver la caja.");
					int saldo = caja.consultarSaldo();
					logger.log("Hay $<0> en la caja.",1,saldo);

				} catch (Exception &ex) {
					logger.log(ex.what());
				}
			}
		} catch (MemoriaCompartidaException &e) {
			logger.log(e.what());
			logger.log("Finaliza el Administrador por error.");
			return -1;
	}
	} catch (Exception &e) {
		cout<<"ADMINISTRADOR: Error al iniciar el Logger, finaliza el Administrador."<<endl;
		return -1;
	}

	return 0;
}
