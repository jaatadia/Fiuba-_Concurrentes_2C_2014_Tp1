/*
 * Exception.cpp
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#include "Exception.h"

Exception::Exception(string mje, string cause): mensaje(mje),cause(cause) {

}

const string& Exception::getMensaje() const {
	return mensaje;
}

Exception::~Exception() {
}

const string& Exception::getCause() const {
	return cause;
}

string Exception::what() const {

	return this->mensaje + ": " + this->cause;
}
