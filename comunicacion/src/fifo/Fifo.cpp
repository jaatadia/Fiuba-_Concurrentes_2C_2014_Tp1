#include "Fifo.h"
#include "../lock/OpenLock.h"
Fifo::Fifo(const std::string nombre, Serializador & s ) : nombre(nombre), serializador(s), fd(-1), lock(new OpenLock()) {
	mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );
}

Fifo::~Fifo() {
	delete lock;
}

void Fifo::cerrar() {
	close ( fd );
	fd = -1;
}

void Fifo::eliminar() const {
	unlink ( nombre.c_str() );
}

Fifo::Fifo(const std::string nombre,Serializador & s, Lock* lock): nombre(nombre), serializador(s), fd(-1), lock(lock) {
	mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );
}

void Fifo::getLock() {
	this->lock->acquire();
}

void Fifo::unlock() {
	this->lock->free();
}
