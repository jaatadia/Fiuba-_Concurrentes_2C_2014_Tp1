/*
 * Exception.h
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_
#include <string>
using namespace std;

class Exception {
private:
	string mensaje;
public:
	Exception(string mje);
	~Exception();
	const string& getMensaje() const;
};

#endif /* EXCEPTION_H_ */
