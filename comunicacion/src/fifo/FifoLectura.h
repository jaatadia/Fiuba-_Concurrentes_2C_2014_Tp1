#ifndef FIFOLECTURA_H_
#define FIFOLECTURA_H_

#include "Fifo.h"

class FifoLectura : public Fifo {
public:
	FifoLectura(const std::string nombre);
	FifoLectura(const std::string nombre, Lock * lock);
	~FifoLectura();

	void abrir();
	ssize_t leer(void* buffer,const ssize_t buffsize);
};

#endif /* FIFOLECTURA_H_ */
