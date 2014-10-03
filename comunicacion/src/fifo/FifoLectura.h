#ifndef FIFOLECTURA_H_
#define FIFOLECTURA_H_

#include "Fifo.h"
#include "../transferencia/Mensaje.h"

/**
 * Permite abrir una fifo en modo lectura y recibir mensajes a traves de ella.
 */
class FifoLectura : public Fifo {
public:
	FifoLectura(const std::string nombre, Serializador & s);
	~FifoLectura();

	/**
	 * Deja lista la fifo para recibir datos
	 */
	void abrir();
	/**
	 * Lee un mensaj de la fifo.
	 * Para errores ver Serializador.h
	 */
	Mensaje * leer();
};

#endif /* FIFOLECTURA_H_ */
