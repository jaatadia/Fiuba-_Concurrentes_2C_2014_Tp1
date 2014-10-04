//============================================================================
// Name        : calesita_p.cpp
// Author      : jtierno
// Version     :
// Description : TODO
//============================================================================

#include <iostream>

#include "src/constantes.h"
#include <sys/types.h>
#include <unistd.h>
#include "src/seniales/SignalHandler.h"
#include "src/seniales/GracefullQuitter.h"
#include "src/seniales/Interrupter.h"

int main() {
	pid_t child_process = fork();
	if (child_process == 0){
		GracefullQuitter quit;
		Interrupter interrupt;
		SignalHandler::getInstance()->registrarHandler(SIGUSR1,&quit);
		SignalHandler::getInstance()->registrarHandler(SIGUSR2,&interrupt);
		while(quit.alive()){
			sleep(5);
		}

		SignalHandler::destruir();

	}else{

	}


}
