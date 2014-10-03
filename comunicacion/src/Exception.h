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
	string cause;
public:
	Exception(string mje, string cause);
	virtual ~Exception();
	const string& getMensaje() const;
	const string& getCause() const;
	virtual string what() const;
};

#endif /* EXCEPTION_H_ */
