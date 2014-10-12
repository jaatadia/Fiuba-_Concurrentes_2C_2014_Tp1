/*
 * SignalException.h
 *
 *  Created on: 12/10/2014
 *      Author: jonathan
 */

#ifndef SIGNALEXCEPTION_H_
#define SIGNALEXCEPTION_H_

#include "../Exception.h"

class SignalException: public Exception {
public:
	SignalException(string mje, string cause);
	~SignalException();
};

#endif /* SIGNALEXCEPTION_H_ */
