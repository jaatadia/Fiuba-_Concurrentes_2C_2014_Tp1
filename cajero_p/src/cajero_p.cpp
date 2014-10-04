//============================================================================
// Name        : cajero_p.cpp
// Author      : jtierno
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Expendio.h"
#include "src/transferencia/MensajeCompraBoleto.h"
#include <string>
#include "src/Exception.h"
#include "src/logger/Logger.h"
#include "src/constantes.h"
using namespace std;

int main(int argc, char* argv[]) {
	int nroBoleto = NRO_BOLETO_INVALIDO + 1;
	int precioBoleto = 10;
	if(argc>2){
		//TODO CARGAR DE PARAMETROS EL PRECIO DEL BOLETO.
	}
	try {
		cout << "Soy el cajero" << endl;
		Expendio e(precioBoleto);
		int i = 0;
		while (true) {
			cout << "esperando cliente" << endl;
			int plataNinio = e.recibirNinio();
			cout << "llega cliente nro: " << i << endl;
			if(plataNinio>= precioBoleto){
				cout << "venta concretada" << endl;
				e.darBoleto(nroBoleto++);
			} else {
				cout << "el pibe era re pobre" << endl;
				e.rechazarPagoInsuficiente();
			}
			i++;
		}
	} catch (Exception & e) {
		cout << e.what() << endl;

	}
	return 0;
}
