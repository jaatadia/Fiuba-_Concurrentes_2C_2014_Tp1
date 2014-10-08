/*
 * MensajeCompraBoleto.h
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#ifndef MENSAJEINT_H_
#define MENSAJEINT_H_
#include "Mensaje.h"
#include <string>
/**
 * Mensaje para la compra-venta de boletos.
 */
class MensajeInt: public Mensaje {
private:
	int numero; //el importe
public:
	MensajeInt(int numero);
	~MensajeInt();
	virtual Mensaje * deserializar(string const contenido) const;
	virtual string serializar() const;
	int getInt() const;
};

#endif /* MENSAJEINT_H_ */
