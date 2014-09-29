//============================================================================
// Name        : cajero_p.cpp
// Author      : jtierno
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Expendio.h"
using namespace std;

int main() {
	cout << "Soy el cajero" << endl;
	Expendio e;
	int i = 0;
	while(true){
		cout << "esperando cliente" << endl;
		e.esperarCliente();
		cout << "llega cliente nro: "<< i << endl;
		e.darBoleto();
		cout << "venta concretada" << endl;
		i++;
	}
	return 0;
}
