#include "FifoLectura.h"

FifoLectura::FifoLectura(const std::string nombre, Serializador & s) : Fifo(nombre,s) {
}
FifoLectura::FifoLectura(const std::string nombre, Serializador & s, Lock* lock) : Fifo(nombre,s,lock) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
	fd = open ( nombre.c_str(),O_RDONLY );
}


Mensaje * FifoLectura::leer() {
	this->getLock();
	Mensaje* mje = this->serializador.recibir(this->fd);
	this->unlock();
	return mje;
}
