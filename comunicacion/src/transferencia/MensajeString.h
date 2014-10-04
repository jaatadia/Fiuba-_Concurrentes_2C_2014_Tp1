/*
 * MensajeString.h
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#ifndef MENSAJESTRING_H_
#define MENSAJESTRING_H_
#include "Mensaje.h"
#include <string>


/*
 * Mensaje simple con un solo campo String, NO ES PARA CONCATENAR COSAS EN ESE STRING.
 */
class MensajeString: public Mensaje {
private:
	string mensaje;
public:
	MensajeString(string msj);
	/**
	 * Crea un mensaje del mismo tipo pero con los datos del string.
	 */
	virtual Mensaje * deserializar(string const contenido) const;
	/**
	 * crea el una representacion en string.
	 */
	virtual string serializar() const;

	~MensajeString();
};

#endif /* MENSAJESTRING_H_ */
