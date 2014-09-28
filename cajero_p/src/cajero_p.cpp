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
	cout << "esperando cliente" << endl;
	Expendio e;
	e.esperarCliente();
	e.darBoleto();
	return 0;
}
