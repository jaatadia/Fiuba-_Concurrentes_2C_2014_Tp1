//============================================================================
// Name        : logger.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
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

using namespace std;

//recive en el parametro 1 el nombre del log y si recive un segundo parametro no loggea;
//se mata el proceso mandando SIGUSR1
int main(int argc,char* argv[]) {

	cout<<"Logger PID: "<<getpid()<<endl;


	std::string ARCHIVO_LOGG = "./log";
	if (argc >= 2){
		std::string ARCHIVO_LOGG = argv[1];
	}


	LoggerListener log(ARCHIVO_LOGG); //creo el lector del listener
	SignalHandler::getInstance()->registrarHandler(SIGUSR1,&log);//le paso como handler de la señal sigusr1
	if (argc == 3) log.mute();

	log.start();
	while (log.alive()){//mientras el log se encuentre activo
		log.listen();//le digo que escuche mensajes y los escriba
	}

}
