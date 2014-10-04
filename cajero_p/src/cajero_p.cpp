//============================================================================
// Name        : cajero_p.cpp
// Author      : jtierno
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <string>
#include "src/seniales/SignalHandler.h"
#include "src/seniales/GracefullQuitter.h"

#include "Expendio.h"
#include "Caja.h"
#include "src/transferencia/MensajeCompraBoleto.h"
#include "src/Exception.h"
#include "src/InterrumpidoException.h"
#include "src/logger/Logger.h"
#include "src/constantes.h"
using namespace std;

int main(int argc, char* argv[]) {
	int nroBoleto = NRO_BOLETO_INVALIDO + 1;
	int precioBoleto = 10;
	if(argc>2){
		//TODO CARGAR DE PARAMETROS EL PRECIO DEL BOLETO.
	}
	//Inicializo el quitter.
	GracefullQuitter grace;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &grace); //le paso como handler de la señal sigusr1

	try {
		Logger logger("CAJERO");
		logger.log("Iniciando venta");
		Expendio e(precioBoleto);
		Caja caja;
		int i = 1;
		while (grace.alive()) {
			try {
				logger.log("Esperando Ninio");
				int plataNinio = e.recibirNinio();

				logger.log("Llega el ninio nro <0>", 1,i);
				if(plataNinio>= precioBoleto){
					caja.almacenarDinero(precioBoleto);
					logger.log("Se guardaron $<0> en la caja", 1,precioBoleto);

					e.darBoleto(nroBoleto++);
					logger.log("Se vendio el boleto nro <0>", 1,nroBoleto-1);
				} else {
					e.rechazarPagoInsuficiente();
					logger.log("No se pudo vender boleto ya que no tenia suficiente dinero");
				}
				i++;
			} catch (InterrumpidoException & ex) {
				// Si me interrumpieron esperando un cliente.
				cout<<"Se interrumpio la espera de ninio por una signal." << endl;
			}
		}
	} catch (Exception & e) {
		cout << e.what() << endl;

	}
	cout<< "Terminando proceso de cajero"<<endl;
	return 0;
}
