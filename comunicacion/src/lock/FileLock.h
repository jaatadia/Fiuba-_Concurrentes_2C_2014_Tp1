/*
 * FileLock.h
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#ifndef FILELOCK_H_
#define FILELOCK_H_

#include "Lock.h"
#include <string>
using namespace std;

/**
 * Clase que hace lock sobre un archivo.
 */
class FileLock: public Lock {

public:
	FileLock(string nombre);
	~FileLock();
	void acquire();
	void free();

};

#endif /* FILELOCK_H_ */
