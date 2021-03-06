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
#include "../seniales/SignalHandler.h"
using namespace std;

Proceso::Proceso(const string path, Parametros & params) :
		pid(-1), log(NULL) {
	run(path, params);
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
	this->pid = fork();
	if (pid == ERR_CODE) {
		throw ProcesoException("Error creando el nuevo proceso",
				strerror(errno));
	}

	if (pid == 0) {
		params.pushFirst(path);
		if (log == NULL) {
			cout << "Iniciando proceso con la imagen " << path << endl;
		} else {
			log->log("Iniciando proceso con la imagen " + path);
		}
		int res = execv(path.c_str(), params.getContenido());
		if (res == ERR_CODE) {
			string err(strerror(errno));
			if (log == NULL) {
				cout << "Error cargando la imagen del nuevo proceso: " << err << endl;
			} else {
				log->log("Error cargando la imagen del nuevo proceso: " + err);
			}
			exit(EXIT_FAILURE);
		}
	}
}

Proceso::Proceso(const string path) :
		pid(-1), log(NULL) {
	Parametros params;
	run(path, params);
}

Proceso::Proceso(const string path, Parametros& params, Logger* log) :
		pid(-1), log(log) {
	run(path, params);
}

Proceso::Proceso(const string path, Logger* log) :
		pid(-1), log(log) {
	Parametros params;
	run(path, params);
}

