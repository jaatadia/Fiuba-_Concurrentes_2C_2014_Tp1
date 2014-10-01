/*
 * Exception.cpp
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#include "Exception.h"

Exception::Exception(string mje, string cause): mensaje(mje),cause(cause) {
	// TODO Auto-generated constructor stub

}

const string& Exception::getMensaje() const {
	return mensaje;
}

Exception::~Exception() {
	// TODO Auto-generated destructor stub
}

const string& Exception::getCause() const {
	return cause;
}
