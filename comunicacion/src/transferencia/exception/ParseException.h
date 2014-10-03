/*
 * ParseException.h
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#ifndef PARSEEXCEPTION_H_
#define PARSEEXCEPTION_H_
#include <string>
#include "../../Exception.h"
using namespace std;

class ParseException: public Exception {
public:
	ParseException(string mje);
	virtual ~ParseException();
};

#endif /* PARSEEXCEPTION_H_ */
