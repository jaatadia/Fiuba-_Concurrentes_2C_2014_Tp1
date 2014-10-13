//============================================================================
// Name        : calesita_p.cpp
// Author      : jtierno
// Version     :
// Description :
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
#include "src/Exception.h"
#include "src/ColaController.h"


int main(int argc,char* argv[]) {
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
		ColaController cola(CALESITA);
		log.log("Empezando primera vez");
		while(quit.alive()){
				log.log("Esperando ninos");
				while(quit.alive()  && ( ( (!ent.estaLlena()) && cola.next()) || ent.estaVacia() )){
					ent.proximo();
				}
				if(!quit.alive()){
					log.log("Terminando calesita");
					SignalHandler::destruir();
					return 0;
				}
				log.log("Esperando que los niños terminen de sentarse");
				ent.esperarSienten();
				ent.comenzarVuelta();
				log.log("Termino la vuelta");
				ent.liberar();
				log.log("Esperando que los niños salgan");
				ent.reset();
				log.log("Todos los niños salieron");
				std::cout<<"Programa terminado correctamente"<<std::endl;
		}
	}catch(Exception &e){
		log.log(e.what());
	}
	log.log("Terminando calesita");
	SignalHandler::destruir();
	return 0;
}

