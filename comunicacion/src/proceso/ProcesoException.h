/*
 * ProcesoException.h
 *
 *  Created on: 04/10/2014
 *      Author: jonathan
 */

#ifndef PROCESOEXCEPTION_H_
#define PROCESOEXCEPTION_H_

#include "../Exception.h"

class ProcesoException: public Exception {
public:
	ProcesoException(string msj, string causa);
	~ProcesoException();
};

#endif /* PROCESOEXCEPTION_H_ */
