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

class Mensaje {
private:
	char tipo;

public:
	Mensaje(char tipo);
	Mensaje();
	Mensaje(const Mensaje &);
	void  operator= (const Mensaje & v);
	virtual ~Mensaje();
	char getTipo() const;
	void setTipo(char tipo);
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
