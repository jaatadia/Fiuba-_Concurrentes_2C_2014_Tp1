/*
 * ComunicacionException.cpp
 *
 *  Created on: 1/10/2014
 *      Author: jonathan
 */

#include "ComunicacionException.h"

ComunicacionException::ComunicacionException(string msje, string cause):Exception(msje,cause) {

}

ComunicacionException::~ComunicacionException() {
	// TODO Auto-generated destructor stub
}

