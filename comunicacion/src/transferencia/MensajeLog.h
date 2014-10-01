/*
 * MensajeLog.h
 *
 *  Created on: 01/10/2014
 *      Author: jonathan
 */

#ifndef MENSAJELOG_H_
#define MENSAJELOG_H_
#include <string>
#include "Mensaje.h"
using namespace std;

class MensajeLog: public Mensaje {
private:
	string pid;
	string id;
	string hora;
	string mensaje;
public:
	MensajeLog(string pid,string id, string hora, string mensaje);
	~MensajeLog();
	Mensaje * deserializar(string const mje) const;
	string serializar() const;
	const string& getHora() const;
	const string& getId() const;
	const string& getMensaje() const;
	const string& getPid() const;
};

#endif /* MENSAJELOG_H_ */
