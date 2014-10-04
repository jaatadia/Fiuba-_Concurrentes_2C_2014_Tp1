/*
 * InterrumpidoException.h
 *
 *  Created on: 03/10/2014
 *      Author: jonathan
 */

#ifndef INTERRUMPIDOEXCEPTION_H_
#define INTERRUMPIDOEXCEPTION_H_

#include "Exception.h"

/**
 * Excepcion para cuando un proceso es interrumpido por una senial
 */
class InterrumpidoException: public Exception {
public:
	InterrumpidoException(string mje, string cause);
	~InterrumpidoException();
};

#endif /* INTERRUMPIDOEXCEPTION_H_ */
