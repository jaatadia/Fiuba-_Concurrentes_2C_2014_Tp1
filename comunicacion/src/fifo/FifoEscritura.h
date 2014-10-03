#ifndef FIFOESCRITURA_H_
#define FIFOESCRITURA_H_

#include "Fifo.h"
#include "../transferencia/Mensaje.h"
/**
 * Permite enviar datos a traves de una fifo abierta para escritura.
 */

class FifoEscritura : public Fifo {

public:
	FifoEscritura(const std::string nombre, Serializador &);
	~FifoEscritura();

	/**
	 * Abre la fifo para comenzar a enviar datos
	 */
	void abrir();
	/**
	 * Escribe el mensaje y lo consume.
	 * Para errores ver Serializador.h
	 */
	void escribir(Mensaje * mje) ;
};

#endif /* FIFOESCRITURA_H_ */
