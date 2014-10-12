//============================================================================
// Name        : ninio_p.cpp
// Author      : jtierno
// Version     :
// Description : Proceso ninio que quiere pasear por la calesita.
//============================================================================

#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "Boleteria.h"
#include "DineroInsuficienteException.h"
#include "src/lock/LockException.h"
#include "src/logger/Logger.h"


#include "Calesita.h"

using namespace std;
/**
 * Recibe como parametros 0 y 1 el nombre del ejecutable y el pid del padre.
 */

string determinarSexo() {
	int sexo = rand() % 2;
	switch (sexo) {
	case 0:
		return "NINIO";
	default:
		return "NINIA";
		break;
	}
	return "NINIO";
}

string determinarGorro() {
	int sexo = rand() % 2;
	switch (sexo) {
	case 0:
		return "(con gorrito";
	default:
		return "(sin gorrito";
		break;
	}
	return "(";
}

string determinarPaleta() {
	int sexo = rand() % 2;
	switch (sexo) {
	case 0:
		return " y con paleta)";
	default:
		return " y sin paleta)";
		break;
	}
	return ")";
}

string deteminarCodigo() {
	srand(time(NULL));
	ostringstream ss;
	ss << determinarSexo() << determinarGorro() << determinarPaleta();
	string codigo = ss.str();
	return codigo;
}

/* recibe en argv[1] la cantidad de asientos de la calesita */
int main(int argc, char* argv[]) {

	int cantAsientos = atoi(argv[1]);
	int boleto = -1;
	Logger logger(deteminarCodigo());
	logger.log("Voy a correr hacia la boleteria");

	//---------------------Boleteria--------------------
	try {
		Boleteria b;
		int dineroDisponible = 10;
		logger.log("Intenta comprar boleto con $<0>", 1, dineroDisponible);
		boleto = b.comprar(dineroDisponible);
		logger.log("Compro boleto Nro: <0>", 1, boleto);
	} catch (DineroInsuficienteException & e) {
		//LOGGER dar un mensaje que no se pudo comprar el boleto por falta de dinero y salir.
		logger.log(
				"No se pudo comprar el boleto. Se necesitaban $<0> pero se tenian $<1>. Faltan $<2>",
				3, e.getNecesario(), e.getDisponible(),
				e.getNecesario() - e.getDisponible());
	} catch (LockException & e) {
		logger.log(e.what());
	} catch (Exception & e) {
		cout <<"Fallo del ninio: "<< e.what() << endl;
		//TODO SALIR.
		//TODO sacar cout
	}


	logger.log("Corriendo hacia la calesita");

	/* ------------------- calesita ----------------------------*/
	Calesita cale(&logger);

	logger.log("niño: Esperando en la entrada");
	if(cale.entrar("1030")==CALESITA_NO_PASAR){
		logger.log("No pude entrar :(");
		return -1;
	}
	logger.log("niño: Entré a la calesita");
	cale.sentarse(10);
	logger.log("niño: me senté");
	cale.esperar();
	logger.log("niño: Terminó la vuelta");
	cale.salir();
	logger.log("niño: Salí");


}

