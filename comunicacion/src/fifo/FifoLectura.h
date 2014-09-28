#ifndef FIFOLECTURA_H_
#define FIFOLECTURA_H_

#include "Fifo.h"
#include "../transferencia/Mensaje.h"
class FifoLectura : public Fifo {
public:
	FifoLectura(const std::string nombre, Serializador & s);
	FifoLectura(const std::string nombre, Serializador & s, Lock * lock);
	~FifoLectura();

	void abrir();
	Mensaje * leer();
};

#endif /* FIFOLECTURA_H_ */
