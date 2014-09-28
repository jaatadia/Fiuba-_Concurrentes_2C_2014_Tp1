#include "FifoLectura.h"

FifoLectura::FifoLectura(const std::string nombre) : Fifo(nombre) {
}
FifoLectura::FifoLectura(const std::string nombre, Lock* lock) : Fifo(nombre,lock) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
	fd = open ( nombre.c_str(),O_RDONLY );
}


ssize_t FifoLectura::leer(void* buffer,const ssize_t buffsize) {
	this->getLock();
	ssize_t i  = read ( fd,buffer,buffsize );
	this->unlock();
	return i;
}
