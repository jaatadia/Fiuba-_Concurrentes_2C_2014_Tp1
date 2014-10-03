//============================================================================
// Name        : cajero_p.cpp
// Author      : jtierno
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Expendio.h"
#include "src/transferencia/MensajeLog.h"
#include <string>
#include "src/Exception.h"
#include "src/logger/Logger.h"
using namespace std;

int main() {
try {
			Logger log("") ;
			log.log("mensaje prueba 2");
			log.log("varios");
			log.log("mensajes");
			log.log("uno");
			log.log("atras del otro");

} catch (Exception & e) {
	cout << e.getMensaje() << ": "<< e.getCause();
}
//	cout << "Soy el cajero" << endl;
//	Expendio e;
//	int i = 0;
//	while(true){
//		cout << "esperando cliente" << endl;
//		e.esperarCliente();
//		cout << "llega cliente nro: "<< i << endl;
//		e.darBoleto();
//		cout << "venta concretada" << endl;
//		i++;
//	}
	return 0;
}
