/*
 * ProcesoException.cpp
 *
 *  Created on: 04/10/2014
 *      Author: jonathan
 */

#include "ProcesoException.h"

ProcesoException::ProcesoException(string msj, string causa):Exception(msj,causa) {

}

ProcesoException::~ProcesoException() {
}

