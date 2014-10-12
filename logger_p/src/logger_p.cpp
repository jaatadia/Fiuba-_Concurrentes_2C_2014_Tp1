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
#include "src/constantes.h"

using namespace std;

/**
 * Recibe como parametros 0 y
 * Como parametro 1 si es modo -d de debug y si es asi en el 2 el  nombre de archivo.
 */

int main(int argc, char* argv[]) {

	try {

		cout << "Logger PID: " << getpid() << endl;

		std::string ARCHIVO_LOGG = "./log";
		if (argc == 3) {

			string val = string(argv[1]);
			if(val == "-d"){
				cout << "Logger Iniciado en modo DEBUG, loggeando en el archivo " << argv[2] <<endl;
				ARCHIVO_LOGG = argv[2];
			}
		}

		GracefullQuitter grace;
		SignalHandler::getInstance()->registrarHandler(QUIT_SIGNAL, &grace); //le paso como handler de la señal sigusr1

		LoggerListener log(ARCHIVO_LOGG); //creo el lector del listener
		if (argc != 3){
			log.mute();
		}
		while (grace.alive()) { //mientras el log se encuentre activo
			log.listen(); //le digo que escuche mensajes y los escriba
		}
	} catch (Exception & e) {
		cout <<"Fallo el logger: "<<e.what();
	}catch (...){
		cout<<"Fallo el logger: error desconocido";
	}
	SignalHandler::destruir();

}
