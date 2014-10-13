//============================================================================
// Name        : ninio_p.cpp
// Author      : jtierno
// Version     :
// Description : Proceso ninio que quiere pasear por la calesita.
//============================================================================

//TODO ninio_p retorna -1 en caso de error por excepcion,
//el q lo llama deberia cerrar las cosas para q no queden

#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "Boleteria.h"
#include "DineroInsuficienteException.h"
#include "src/lock/LockException.h"
#include "src/logger/Logger.h"
#include "src/constantes.h"
#include "src/Exception.h"
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


int elegirAsiento(int cant_asientos){
	return calcularRandom() % cant_asientos;
}

/**************************************************************************************/
/* recibe en argv[1] el nro de ninio y en argv[2] la cantidad de asientos de la calesita*/

int main(int argc, char* argv[]) {

	int id_ninio=atoi(argv[1]);
	int cantAsientos = atoi(argv[2]);
	int boleto = -1;
	Logger logger(deteminarCodigo());

	logger.log("(nro:<0>) Voy a correr hacia la boleteria",1,id_ninio);

	//---------------------Boleteria--------------------
/*	try {
		Boleteria b;
		int dineroDisponible = 10;

		logger.log("(nro:<0>) Intenta comprar boleto con $<1>", 2, id_ninio, dineroDisponible);
		boleto = b.comprar(dineroDisponible);

		logger.log("(nro:<0>) Compró boleto Nro: <1>", 2, id_ninio, boleto);
	} catch (DineroInsuficienteException & e) {
		//LOGGER dar un mensaje que no se pudo comprar el boleto por falta de dinero y salir.
		logger.log(

				"(nro:<0>) No pude comprar el boleto. Necesitaba $<1> pero tenía $<2>. Me faltan $<3>",
				4, id_ninio, e.getNecesario(), e.getDisponible(),
				e.getNecesario() - e.getDisponible());
	} catch (LockException & e) {
		logger.log("Fallo del ninio nro:<0>"+e.what(),1,id_ninio);
	} catch (Exception & e) {
		logger.log("Fallo del ninio nro:<0>"+e.what(),1,id_ninio);
		//TODO SALIR.
	}catch(...){
		logger.log("Fallo del ninio nro:<0>",1,id_ninio);
	}


	logger.log("(nro:<0>) Corriendo hacia la calesita",1,id_ninio);
*/


	/* ------------------- calesita ----------------------------*/
	
	try{
	Calesita cale(id_ninio,&logger,cantAsientos);

		
	logger.log("(nro:<0>) Esperando en la entrada",1,id_ninio);
	if(cale.entrar("1030")==CALESITA_NO_PASAR){ //TODO (!) cambiar ese nro RE MAGICO
		logger.log("(nro:<0>) No pude entrar :",1,id_ninio);
		return -1;
	}
	logger.log("(nro:<0>) Entré a la calesita",1,id_ninio);
	int asiento_elegido = elegirAsiento(cantAsientos);
	cale.sentarse(asiento_elegido);
	logger.log("(nro:<0>) Me senté",1,id_ninio);
	cale.esperar();
	logger.log("(nro:<0>) Terminó la vuelta",1,id_ninio);
	cale.salir();
	logger.log("(nro:<0>) Salí",1,id_ninio);
	} catch (Exception &e) {
		cout<<"se rompio"<<endl;
		logger.log("Fallo del ninio id:<0>"+e.what(),1,id_ninio);
		return -1;
	}

	return 0;
}

