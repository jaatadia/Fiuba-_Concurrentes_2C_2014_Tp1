#include "Fifo.h"
#include "../lock/OpenLock.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../constantes.h"
#include "../Exception.h"

Fifo::Fifo(const std::string nombre, Serializador & s ) : nombre(nombre), serializador(s), fd(-1) {

	int result = this->crearArchivo(nombre) ;
	if (result == ERR_CODE){
		if(errno == EEXIST){
			cout << "El archivo "<< nombre << " para la FIFO ya estaba creado al querer crearlo"<< std::endl;
		} else {
			throw Exception("No se pudo crear la fifo", strerror(errno));
		}
	}
}

Fifo::~Fifo() {
}

void Fifo::cerrar() {
	if(close ( fd ) == ERR_CODE){
		throw Exception("No se pudo cerrar la fifo", strerror(errno));
	}
	fd = -1;
}

void Fifo::eliminar() {
	if(unlink ( nombre.c_str() )==ERR_CODE){
		throw Exception("No se pudo eliminar la fifo", strerror(errno));
	}
}

int Fifo::crearArchivo(const string& str) {
	return mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );
}

const std::string& Fifo::getNombre() const {
	return nombre;
}
