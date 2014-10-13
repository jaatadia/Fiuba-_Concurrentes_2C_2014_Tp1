#include "FifoLectura.h"
#include "../constantes.h"
#include "../Exception.h"
#include "../InterrumpidoException.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
FifoLectura::FifoLectura(const std::string nombre, Serializador & s) : Fifo(nombre,s) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
	fd = open ( nombre.c_str(),O_RDONLY );
	if(fd == ERR_CODE){
		if(errno == EINTR){
			throw InterrumpidoException("No se pudo abrir la cola","Interrumpido por señal");
		}
		throw Exception("No se pudo abrir la fifo para lectura", strerror(errno));
	}
}


Mensaje * FifoLectura::leer() {
	Mensaje* mje = this->serializador.recibir(this->fd);
	return mje;
}

Mensaje * FifoLectura::leer_timeout(int secs) {
	Mensaje* mje = this->serializador.recibir_timeout(this->fd,secs);
	return mje;
}
