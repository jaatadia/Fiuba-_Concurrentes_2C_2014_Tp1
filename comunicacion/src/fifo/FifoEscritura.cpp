#include "FifoEscritura.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../constantes.h"
#include "../Exception.h"
FifoEscritura::~FifoEscritura() {
}

void FifoEscritura::abrir() {
	fd = open ( nombre.c_str(),O_WRONLY );
	if(fd == ERR_CODE){
		throw Exception("No se pudo abrir la fifo para escritura",strerror(errno));
	}
}


FifoEscritura::FifoEscritura(const std::string nombre, Serializador & s): Fifo(nombre,s) {
}

void FifoEscritura::escribir(Mensaje * mje) {
	this->serializador.enviar(this->fd , mje);
}
