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

static const string SEPARADOR = "|";
/**
 * Abstraccion de un mensaje que se serializa y envia para luego ser recibido y desserializado.
 */
class Mensaje {
private:
	string tipo;
public:
	Mensaje(string tipo);
	Mensaje();
	Mensaje(const Mensaje &);
	void  operator= (const Mensaje & v);
	virtual ~Mensaje();
	string getTipo() const;
	/**
	 * Crea un mensaje del mismo tipo pero con los datos del string.
	 */
	virtual Mensaje * deserializar(string const contenido) const;
	/**
	 * crea el una representacion en string.
	 */
	virtual string serializar() const;
};


#endif /* MENSAJE_H_ */
