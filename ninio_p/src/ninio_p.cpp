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
#include "src/constantes.h"


#include "Calesita.h"

using namespace std;


int calcularRandom () {
	srand ( time(NULL) );
	int resultado = rand() % MAX_NINIO_RND;
	return resultado+1;
}

string determinarSexo() {
	int sexo = calcularRandom() % 2;
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
	int sexo = calcularRandom() % 2;
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
	int sexo = calcularRandom() % 2;
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

/**************************************************************************************/
/* recibe en argv[1] el nro de ninio y en argv[2] la cantidad de asientos de la calesita*/

int main(int argc, char* argv[]) {

	int id_ninio=atoi(argv[1]);
	int cantAsientos = atoi(argv[2]);
	int boleto = -1;
	Logger logger(deteminarCodigo()); //TODO y si el logger tira excepcion?

	//---------------------Boleteria--------------------
	try {
		Boleteria b;
		int dineroDisponible = 10;
		logger.log("(id:<0>) Intenta comprar boleto con $<1>", 2, id_ninio, dineroDisponible);
		boleto = b.comprar(dineroDisponible);
		logger.log("(id:<0>) Compró boleto Nro: <1>", 2, id_ninio, boleto);
	} catch (DineroInsuficienteException & e) {
		//LOGGER dar un mensaje que no se pudo comprar el boleto por falta de dinero y salir.
		logger.log(
				"(id:<0>) No pude comprar el boleto. Necesitaba $<1> pero tenía $<2>. Me faltan $<3>",
				4, id_ninio, e.getNecesario(), e.getDisponible(),
				e.getNecesario() - e.getDisponible());
	} catch (LockException & e) {
		logger.log(e.what());
	} catch (Exception & e) {
		logger.log("Fallo del ninio id:<0>");
		logger.log(e.what());
		//TODO SALIR.
	}


	/* ------------------- calesita ----------------------------*/
	Calesita cale(&logger);

	logger.log("Esperando en la entrada"); //TODO flor - poner id de ninios
	if(cale.entrar("1030")==CALESITA_NO_PASAR){ //TODO (!) cambiar ese nro RE MAGICO
		logger.log("No pude entrar :(");
		return -1;
	}
	logger.log("Entré a la calesita");
	cale.sentarse(10); //TODO flor - elige random un nro de asiento preferido
	logger.log("Me senté");
	cale.esperar();
	logger.log("Terminó la vuelta");
	cale.salir();
	logger.log("Salí");

return 0;
}

