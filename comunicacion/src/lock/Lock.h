/*
 * Lock.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef LOCK_H_
#define LOCK_H_

class Lock {
public:
	Lock(){};
	virtual ~Lock(){};
	virtual void acquire() = 0;
	virtual void free() = 0;
};

#endif /* LOCK_H_ */
