//============================================================================
// Name        : cajero_p.cpp
// Author      : jtierno
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
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
		cout<< "Iniciando cajero"<<endl;
		Expendio e(precioBoleto);
		Caja caja;
		int i = 0;
		while (grace.alive()) {
			try {
				cout << "Esperando Ninio" << endl;
				int plataNinio = e.recibirNinio();
				cout << "Llega el Ninio nro: " << i << endl;
				if(plataNinio>= precioBoleto){
					caja.almacenarDinero(precioBoleto);
					e.darBoleto(nroBoleto++);
					cout << "Venta concretada" << endl;
				} else {
					cout << "No se pudo vender boleto ya que no tenia suficiente dinero" << endl;
					e.rechazarPagoInsuficiente();
				}
				i++;
			} catch (InterrumpidoException & ex) {
				// Si me interrumpieron vendiendo un boleto, rechazo el pago
				cout<<"Se interrumpio la espera de ninio por una signal." << endl;
			}
		}
	} catch (Exception & e) {
		cout << e.what() << endl;

	}
	cout<< "Terminando proceso de cajero"<<endl;
	return 0;
}
