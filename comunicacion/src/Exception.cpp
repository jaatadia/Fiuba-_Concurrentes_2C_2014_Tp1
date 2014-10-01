/*
 * Exception.cpp
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#include "Exception.h"

Exception::Exception(string mje): mensaje(mje) {
	// TODO Auto-generated constructor stub

}

const string& Exception::getMensaje() const {
	return mensaje;
}

Exception::~Exception() {
	// TODO Auto-generated destructor stub
}

