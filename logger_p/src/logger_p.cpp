//============================================================================
// Name        : logger.cpp
// Author      : jaatadia
// Version     :
// Description : Proceso que recibe el logging, lo imprime y almacena de forma correcta.
//============================================================================

#include <iostream>

#include <sys/types.h>
#include <unistd.h>

#include <string>
#include <string.h>
#include <errno.h>

#include <signal.h>
#include "LoggerListener.h"
#include "src/seniales/SignalHandler.h"
#include "src/seniales/GracefullQuitter.h"
#include "src/Exception.h"

using namespace std;

/**
 * Recibe como parametros 0 y 1 el nombre del ejecutable y el pid del padre.
 * Como parametro 2 si es modo -d de debug y si es asi en el 3 el  nombre de archivo.
 */

//recive en el parametro 1 el nombre del log y si recive un segundo parametro no loggea;
//se mata el proceso mandando SIGUSR1
int main(int argc, char* argv[]) {

	try {

		cout << "Logger PID: " << getpid() << endl;

		std::string ARCHIVO_LOGG = "./log";
		if (argc >3) {
			string val = string(argv[2]);
			if(val == "-d"){
				cout << "Logger Iniciado en modo DEBUG, loggeando en el archivo " << argv[3] <<endl;
				std::string ARCHIVO_LOGG = argv[3];
			}
		}

		GracefullQuitter grace;
		SignalHandler::getInstance()->registrarHandler(SIGUSR1, &grace); //le paso como handler de la señal sigusr1

		LoggerListener log(ARCHIVO_LOGG); //creo el lector del listener
		if (argc == 3)
			log.mute();
		while (grace.alive()) { //mientras el log se encuentre activo
			log.listen(); //le digo que escuche mensajes y los escriba
		}
	} catch (Exception & e) {
		cout << e.getMensaje() << ": " << e.getMensaje() << endl;
	}
	SignalHandler::destruir();

}
