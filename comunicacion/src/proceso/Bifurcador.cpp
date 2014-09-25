/*
 * Bifurcador.cpp
 *
 *  Created on: 25/9/2014
 *      Author: jonathan
 */

#include "Bifurcador.h"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;

Bifurcador::Bifurcador() {

}

void Bifurcador::crearHijo(const string path) const {
	pid_t pid = fork ();

	if ( pid == 0 ) {
		cout << "hijo"<<endl;
	} else {
	}

}

Bifurcador::~Bifurcador() {
	// TODO Auto-generated destructor stub
}

