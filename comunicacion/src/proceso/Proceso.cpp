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
#include "ProcesoException.h"
#include <sstream>
#include "Parametros.h"
using namespace std;

Proceso::Proceso(const string path, Parametros & params) :
		pid(-1) {
	run(path,params);
}

Proceso::~Proceso() {
}

int Proceso::getPid() const {
	return pid;
}

void Proceso::setPid(int pid) {
	this->pid = pid;
}

void Proceso::run(const string path, Parametros& params) {
	pid_t parentPid = getpid();
		pid_t pid = fork();
		if (pid == ERR_CODE) {
			throw ProcesoException("Error creando el nuevo proceso",
					strerror(errno));
		}

		if (pid == 0) {
			params.pushFirst(parentPid);
			params.pushFirst(path);
			cout << "cargando la imagen" << path << endl;
			int res = execv(path.c_str(), params.getContenido());
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
				exit(EXIT_FAILURE);
			}
		} else {
			this->pid = pid;
		}
}

Proceso::Proceso(const string path):pid(-1) {
	Parametros params;
	run(path,params);
}
