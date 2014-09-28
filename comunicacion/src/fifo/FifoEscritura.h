#ifndef FIFOESCRITURA_H_
#define FIFOESCRITURA_H_

#include "Fifo.h"
class FifoEscritura : public Fifo {

public:
	FifoEscritura(const std::string nombre, Lock * lock);
	FifoEscritura(const std::string nombre);
	~FifoEscritura();

	void abrir();
	void escribir(const void* buffer,const ssize_t buffsize) ;
};

#endif /* FIFOESCRITURA_H_ */
