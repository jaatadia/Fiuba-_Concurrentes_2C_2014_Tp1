/*
 * SignalException.cpp
 *
 *  Created on: 12/10/2014
 *      Author: jonathan
 */

#include "SignalException.h"

SignalException::SignalException(string mje, string cause):Exception(mje,cause) {

}

SignalException::~SignalException() {
}

