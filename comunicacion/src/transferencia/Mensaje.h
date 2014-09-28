/*
 * Mensaje.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef MENSAJE_H_
#define MENSAJE_H_
#include <string>
using namespace std;


class Mensaje {
private:
	char tipo;

public:
	Mensaje(char tipo);
	virtual ~Mensaje();
	char getTipo() const;
	void setTipo(char tipo);
	/**
	 * Carga los atributos de la clase en base al contenido.
	 */
	virtual void deserializar(string contenido) = 0;
	/**
	 * crea el una representacion en string.
	 */
	virtual string serializar() = 0;
};

#endif /* MENSAJE_H_ */
