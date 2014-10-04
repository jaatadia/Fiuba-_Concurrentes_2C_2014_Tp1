//============================================================================
// Name        : ninio_p.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Boleteria.h"
#include "DineroInsuficienteException.h"
using namespace std;

int main() {
	int boleto = -1;
	cout << "ninio comprando" << endl;
	try {
		Boleteria b;
		boleto = b.comprar(100);
		cout << "ninio compro " << boleto << endl;
	} catch (DineroInsuficienteException & e) {
		cout << e.what() << endl;
		//LOGGER dar un mensaje que no se pudo comprar el boleto por falta de dinero y salir.
	} catch (Exception & e){
		cout << e.what() << endl;
		//TODO SALIR.
	}
}
