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
#include "src/Exception.h"


int main(int argc,char* argv[]) {
	//TODO NO TIENE MANEJO DE ERRORES.
	pid_t child_process = fork();
	if (child_process == 0){
		//proceso que interrumpe la lectura bloqueante

		GracefullQuitter quit;
		SignalHandler::getInstance()->registrarHandler(QUIT_SIGNAL,&quit);
		Logger log("CALESITA_HELPER");
		try{
			Interrupter inter;
			while(quit.alive()){
					inter.reenviar();
			}
		}catch(Exception &e){
			log.log(e.what());
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
		SignalHandler::getInstance()->registrarHandler(QUIT_SIGNAL,&quit);

		Logger log("CALESITA");
		try{
			Entrada ent(nroNinos,vuelta,&log,&quit);

			log.log("Calesita: Empezando primera vez");
			while(quit.alive()){
					log.log("Calesita: Esperando ninos");
					while(ent.proxNino()==1);
					log.log("Calesita: Esperando que los niños terminen de sentarse");
					ent.esperarSienten();
					ent.comenzarVuelta();
					log.log("Calesita: Termino la vuelta");
					ent.liberar();
					log.log("Calesita: Esperando que los niños salgan");
					ent.reset();
					log.log("Calesita: Todos los niños salieron");
			}
		}catch(Exception &e){
			log.log(e.what());
		}
		kill(child_process,QUIT_SIGNAL);
		SignalHandler::destruir();
	}
}
