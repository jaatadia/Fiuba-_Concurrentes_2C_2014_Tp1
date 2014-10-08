/*
 * Parametros.h
 *
 *  Created on: 8/10/2014
 *      Author: jonathan
 */

#ifndef PARAMETROS_H_
#define PARAMETROS_H_

#include <string>
#include <vector>
using namespace std;

class Parametros {
private:
	vector<char*> params;
public:
	Parametros();
	void push(unsigned int);
	void push(const string &);
	void pushFirst(unsigned int);
	void pushFirst(const  string &);
	virtual ~Parametros();
	char ** getContenido();
	int getSize();
};

#endif /* PARAMETROS_H_ */
