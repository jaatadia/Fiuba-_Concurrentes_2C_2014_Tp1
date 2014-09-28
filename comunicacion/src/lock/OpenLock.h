/*
 * OpenLock.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef OPENLOCK_H_
#define OPENLOCK_H_

#include "Lock.h"

class OpenLock: public Lock {
public:
	OpenLock();
	~OpenLock();
	void acquire();
	void free();
};

#endif /* OPENLOCK_H_ */
