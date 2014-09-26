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
#include "../constantes.h"
using namespace std;

Proceso::Proceso(const string path) :
		pid(-1) {
	pid_t parentPid = getPid();
	pid_t pid = fork();
	if (pid == ERR_CODE) {
		string err(strerror(errno));
		string msje = "Error creando el nuevo proceso: " + err;
		throw msje;
	}

	if (pid == 0) {
		static char *argv[] = { NULL };
		cout << "cargando la imagen" << path << endl;
		int res = execv(path.c_str(), argv);
		if (res == ERR_CODE) {
			string err(strerror(errno));
			//si esto pasa muere el proceso hijo. no se si hay algo mas por hacer.
			cout << "Error cargando la imagen del nuevo proceso: " << err
					<< endl;
			/**
			 TODO MANDAR UNA SEÑAL AL PADRE INDICANDO QUE NO SE PUDO CREAR EL PROCESO HIJO.
			 ESTE PROCESO PODRIA REGISTRAR UN HANDLER DE SEÑAL O EL QUE PODRÍA REGISTRARLO ES EL QUE LLAMA A
			 ESTE Y SE ENCARGUE EL DE SABER QUE ESTO PUEDE FALLAR DANDO UNA SIGNAL.
			 */
			exit (EXIT_FAILURE);
		}
	} else {
		this->pid = pid;
	}
}

Proceso::~Proceso() {
	// TODO Auto-generated destructor stub
}

int Proceso::getPid() const {
	return pid;
}

void Proceso::setPid(int pid) {
	this->pid = pid;
}
