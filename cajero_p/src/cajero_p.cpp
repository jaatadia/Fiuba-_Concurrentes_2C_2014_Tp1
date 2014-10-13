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
#include "src/ColaController.h"
using namespace std;
#include <stdlib.h>

//recibe como parametro 1 precio del boleto
int main(int argc, char* argv[]) {
	int nroBoleto = NRO_BOLETO_INVALIDO + 1;
	int precioBoleto = 1;
	if(argc==2){
		precioBoleto = atoi(argv[1]);
	}
	//Inicializo el quitter.
	GracefullQuitter grace;
	SignalHandler::getInstance()->registrarHandler(QUIT_SIGNAL, &grace);

	Logger logger("CAJERO");
	try {

		logger.log("Iniciando venta");
		Expendio e(precioBoleto);
		ColaController cola(BOLETERIA);
		Caja caja;
		int i = 1;
		while (grace.alive()) {
			try {
				logger.log("Esperando Niño");
				while(cola.next()==false){
					if(!grace.alive()){
						SignalHandler::destruir();
						logger.log("Terminando proceso de cajero");
						return 0;
					}
				}
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
		logger.log(e.what());
	}
	SignalHandler::destruir();
	logger.log("Terminando proceso de cajero");
	return 0;
}
