/*
 * Proceso.cpp
 *
 *  Created on: 25/9/2014
 *      Author: jonathan
 */

#include "Proceso.h"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
using namespace std;

Proceso::Proceso(const string path):pid(-1) {
	pid_t pid = fork ();
	if(pid==ERR_CODE) {
		string err(strerror (errno));
		string msje = "Error creando el nuevo proceso: " + err ;
		throw msje ;
	}

	if ( pid == 0 ) {
		cout << "hijo"<<endl;
	} else {
		this->pid = pid;
	}
}

void Proceso::crearHijo(const string path) const {


}

Proceso::~Proceso() {
	// TODO Auto-generated destructor stub
}

