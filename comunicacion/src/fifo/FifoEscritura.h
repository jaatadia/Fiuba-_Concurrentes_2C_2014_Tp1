#ifndef FIFOESCRITURA_H_
#define FIFOESCRITURA_H_

#include "Fifo.h"
#include "../transferencia/Mensaje.h"
class FifoEscritura : public Fifo {

public:
	FifoEscritura(const std::string nombre, Serializador &);
	FifoEscritura(const std::string nombre, Serializador &, Lock * lock);
	~FifoEscritura();

	void abrir();
	/**
	 * Escribe el mensaje y lo consume.
	 */
	void escribir(Mensaje * mje) ;
};

#endif /* FIFOESCRITURA_H_ */
