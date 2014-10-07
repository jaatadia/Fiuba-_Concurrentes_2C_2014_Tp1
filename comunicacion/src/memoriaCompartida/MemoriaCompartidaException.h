/*
 * MemoriaCompartidaException.h
 *
 *  Created on: Oct 7, 2014
 */

#ifndef MEMORIACOMPARTIDAEXCEPTION_H_
#define MEMORIACOMPARTIDAEXCEPTION_H_

#include "../Exception.h"

class MemoriaCompartidaException: public Exception {
public:
	MemoriaCompartidaException(string mje, string cause);
	~MemoriaCompartidaException();
	string what() const;
};

#endif /* MEMORIACOMPARTIDAEXCEPTION_H_ */
