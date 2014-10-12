//============================================================================
// Name        : cajero_p.cpp
// Author      : jtierno
// Version     :
// Description : Proceso que se encarga de la venta de Boletos.
//============================================================================

#include <iostream>
#include <sstream>
#include <string>
#include "src/seniales/SignalHandler.h"
#include "src/seniales/GracefullQuitter.h"

#include "Expendio.h"
#include "src/Caja.h"
#include "src/transferencia/MensajeCompraBoleto.h"
#include "src/Exception.h"
#include "src/InterrumpidoException.h"
#include "src/memoriaCompartida/MemoriaCompartidaException.h"
#include "src/logger/Logger.h"
#include "src/constantes.h"
using namespace std;
#include <stdlib.h>

//recibe como parametro 1 precio del boleto
//TODO sacar couts.
int main(int argc, char* argv[]) {
	int nroBoleto = NRO_BOLETO_INVALIDO + 1;
	int precioBoleto = 100;
	if(argc>2){
		precioBoleto = atoi(argv[1]);
	}
	//Inicializo el quitter.
	GracefullQuitter grace;
	SignalHandler::getInstance()->registrarHandler(SIGUSR1, &grace); //le paso como handler de la señal sigusr1

	try {
		Logger logger("CAJERO");
		logger.log("Iniciando venta");
		Expendio e(precioBoleto);
		Caja caja;
		int i = 1;
		while (grace.alive()) {
			try {
				logger.log("Esperando Niño");
				int plataNinio = e.recibirNinio();

				logger.log("Llega el niño nro <0>", 1,i);
				if(plataNinio>= precioBoleto){
					caja.almacenarDinero(precioBoleto);
					logger.log("Se guardaron $<0> en la caja", 1,precioBoleto);

					e.darBoleto(nroBoleto++);
					logger.log("Se vendió el boleto nro <0>", 1,nroBoleto-1);
				} else {
					e.rechazarPagoInsuficiente();
					logger.log("No se pudo vender boleto ya que no tenía suficiente dinero");
				}
				i++;
			} catch (MemoriaCompartidaException &ex) {
				//error de mem compartida
				logger.log(ex.what());
			} catch (InterrumpidoException & ex) {
				// Si me interrumpieron esperando un cliente.
				logger.log("Se interrumpió la espera de niño por una signal.");
			}
		}
	} catch (Exception & e) {
		cout <<"Fallo del cajero: "<<e.what() << endl;

	}
	cout<< "Terminando proceso de cajero"<<endl;
	return 0;
}
