/*
 * ComunicacionException.h
 *
 *  Created on: 1/10/2014
 *      Author: jonathan
 */

#ifndef COMUNICACIONEXCEPTION_H_
#define COMUNICACIONEXCEPTION_H_
#include "../Exception.h"
class ComunicacionException: public Exception {
public:
	ComunicacionException(string msje, string cause);
	virtual ~ComunicacionException();
};

#endif /* COMUNICACIONEXCEPTION_H_ */
