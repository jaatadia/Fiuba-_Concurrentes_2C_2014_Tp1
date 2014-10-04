/*
 * ParseException.cpp
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#include "ParseException.h"

ParseException::ParseException(string mje):Exception(mje,"Mensaje mal formado") {

}


ParseException::~ParseException() {
}

