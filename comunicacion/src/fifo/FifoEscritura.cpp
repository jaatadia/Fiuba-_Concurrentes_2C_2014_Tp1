#include "FifoEscritura.h"


FifoEscritura::~FifoEscritura() {
	delete this->lock;
}

void FifoEscritura::abrir() {
	fd = open ( nombre.c_str(),O_WRONLY );
}

FifoEscritura::FifoEscritura(const std::string nombre, Serializador & s, Lock* lock) : Fifo(nombre,s,lock) {
}

FifoEscritura::FifoEscritura(const std::string nombre, Serializador & s): Fifo(nombre,s) {
}

void FifoEscritura::escribir(Mensaje * mje) {
	this->getLock();
	this->serializador.enviar(this->fd , mje);
	this->unlock();
}
