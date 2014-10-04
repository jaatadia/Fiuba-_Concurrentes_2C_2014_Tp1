/*
 * MensajeCompraBoleto.h
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#ifndef MENSAJECOMPRABOLETO_H_
#define MENSAJECOMPRABOLETO_H_
#include "Mensaje.h"
#include <string>
/**
 * Mensaje para la compra-venta de boletos.
 */
class MensajeCompraBoleto: public Mensaje {
private:
	int importe; //el importe
	int nroBoleto;
public:
	MensajeCompraBoleto(int);
	~MensajeCompraBoleto();
	virtual Mensaje * deserializar(string const contenido) const;
	virtual string serializar() const;
	int getImporte() const;
	int getNroBoleto() const;
	void setNroBoleto(int nroTicket);
};

#endif /* MENSAJECOMPRABOLETO_H_ */
