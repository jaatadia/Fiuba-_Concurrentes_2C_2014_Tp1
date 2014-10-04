/*
 * LockException.cpp
 *
 *  Created on: 04/10/2014
 *      Author: jonathan
 */

#include "LockException.h"

LockException::LockException(string msj, string causa):Exception(msj,causa) {

}

LockException::~LockException() {
}

