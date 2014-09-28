#include "FifoEscritura.h"


FifoEscritura::~FifoEscritura() {
	delete this->lock;
}

void FifoEscritura::abrir() {
	fd = open ( nombre.c_str(),O_WRONLY );
}

FifoEscritura::FifoEscritura(const std::string nombre, Lock* lock) : Fifo(nombre,lock) {
}

FifoEscritura::FifoEscritura(const std::string nombre): Fifo(nombre) {
}

void FifoEscritura::escribir(const void* buffer,const ssize_t buffsize) {
	this->getLock();
	write ( fd,buffer,buffsize );
	this->unlock();
}
