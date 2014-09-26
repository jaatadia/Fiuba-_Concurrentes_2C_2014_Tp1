//============================================================================
// Name        : maestro.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "src/proceso/Proceso.h"
#include "src/constantes.h"
#include <stdio.h>
   #include <sys/wait.h>

using namespace std;

int main() {
	try {
		Proceso br(EJECUTABLE_CAJERO);
	} catch (string e) {

	}

}
