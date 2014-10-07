//============================================================================
// Name        : calesita_p.cpp
// Author      : jtierno
// Version     :
// Description : TODO
//============================================================================



#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#include "src/constantes.h"
#include "src/seniales/SignalHandler.h"
#include "src/seniales/GracefullQuitter.h"

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
		int nroNinos = 5;//niños por vuelta
		int vuelta = 10;//duracion de la vuelta
		if(argc==3){
			int nroNinos = argv[1];
			int vuelta = argv[2];
		}

		GracefullQuitter quit;
		SignalHandler::getInstance()->registrarHandler(SIGUSR1,&quit);

		Entrada ent(nroNinos);
		while(quit.alive()){
			ent.reset();
			while(ent.proxNino()==1);
			sleep(vuelta);
			ent.liberar();
		}
		SignalHandler::destruir();
	}
}
