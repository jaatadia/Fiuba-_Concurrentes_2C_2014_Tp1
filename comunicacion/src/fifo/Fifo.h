#ifndef FIFO_H_
#define FIFO_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../transferencia/Serializador.h"
/*
 * Clase encargada de establecer un vinculo FIFO
 */
class Fifo {
public:
	Fifo(const std::string nombre, Serializador & s );
	virtual ~Fifo();
	/**
	 * Abre la fifo.
	 */
	virtual void abrir() = 0;
	/**
	 * Cierra la fifo.
	 */
	void cerrar();
	/**
	 * Elimina la fifo.
	 */
	void eliminar();
	/**
	 * getter del nombre
	 */
	const std::string& getNombre() const;

protected:
	std::string nombre;
	Serializador & serializador;
	int fd;
private:
	int crearArchivo(const string & str);
};

#endif /* FIFO_H_ */
