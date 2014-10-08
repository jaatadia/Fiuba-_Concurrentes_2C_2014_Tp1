//============================================================================
// Name        : calesita_p.cpp
// Author      : jtierno
// Version     :
// Description : TODO
//============================================================================



#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "src/constantes.h"
#include "src/seniales/SignalHandler.h"
#include "src/seniales/GracefullQuitter.h"
#include "src/logger/Logger.h"

#include "Entrada.h"
#include "Interrupter.h"


int main(int argc,char* argv[]) {
	pid_t child_process = fork();
	if (child_process == 0){
		//proceso que interrumpe la lectura bloqueante
		GracefullQuitter quit;
		SignalHandler::getInstance()->registrarHandler(SIGUSR1,&quit);
		Interrupter inter;
		while(quit.alive()){
			inter.reenviar();
		}
		SignalHandler::destruir();

	}else{
		//proceso que tramita la calesita
		int nroNinos = 3;//niños por vuelta
		int vuelta = 10;//duracion de la vuelta
		if(argc==3){
			nroNinos = atoi(argv[1]);
			vuelta = atoi(argv[2]);
		}

		GracefullQuitter quit;
		SignalHandler::getInstance()->registrarHandler(SIGUSR1,&quit);

		Logger log("./log");

		Entrada ent(nroNinos,vuelta,&log);

		log.log("Calesita: Empezando primera vez");
		ent.reset();
		while(quit.alive()){
			log.log("Calesita: Esperando ninos");
			while(ent.proxNino()==1);
			log.log("Calesita: Esperando que los niños terminen de sentarse");
			ent.esperarSienten();
			log.log("Calesita: Comenzando la vuelta");
			ent.comenzarVuelta();
			log.log("Calesita: Termino la vuelta");
			ent.liberar();
			ent.reset();
			log.log("Calesita: Todos los niños salieron");
		}
		SignalHandler::destruir();
	}
}
