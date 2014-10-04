/*
 * LockException.h
 *
 *  Created on: 04/10/2014
 *      Author: jonathan
 */

#ifndef LOCKEXCEPTION_H_
#define LOCKEXCEPTION_H_

#include "../Exception.h"

/**
 * Excepcion para locks.
 */
class LockException: public Exception {
public:
	LockException(string msj, string causa);
	~LockException();
};

#endif /* LOCKEXCEPTION_H_ */
