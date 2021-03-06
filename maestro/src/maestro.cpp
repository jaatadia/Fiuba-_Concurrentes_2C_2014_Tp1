//============================================================================
// Name        : maestro.cpp
// Author      : jtierno
// Version     :
// Description : Proceso que genera el resto de los procesos.
//============================================================================

#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <list>
#include <unistd.h>

#include "src/constantes.h"
#include "src/proceso/Proceso.h"
#include "src/proceso/ProcesoException.h"
#include "src/logger/Logger.h"
#include "src/proceso/Parametros.h"

#include "src/memoriaCompartida/MemoriaCompartidaException.h"
#include "src/memoriaCompartida/Asientos.h"

using namespace std;


int calcular_random(int min,int max){
	int resultado = rand()%(max-min+1);
	return resultado+min;
}

void bloquearSenialFallo(){

}

//devuelve si match existe en los argv
bool getParam(int argc,char* argv[],const char* match){
	bool found = false;
	for (int i=1;i<argc;i++){
		if(strcmp(argv[i],match)==0){
			found=true;
			break;
		}
	}
	return found;
}


//en exit si match existe en los argv y devuelve el parametro acompañante de match
int getParamInt(int argc,char* argv[],const char* match,bool& exit){
	int result=0;

	bool found = false;
	for (int i=1;i<argc-1;i++){
		if(strcmp(argv[i],match)==0){
			bool valid = true;
			for (unsigned int j=0;j<strlen(argv[i+1]);j++){
				if (!isdigit(argv[i+1][j])){
					valid=false;
					break;
				}
			}
			if(!valid){
				continue;
			}
			found=true;
			result = atoi(argv[i+1]);
			break;
		}
	}
	exit=found;
	return result;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	bool found = getParam(argc,argv,"-h");
	if(found){
		std::cout<<"Trabajo practico de introduccion a los sistemas distribuidos 2ºC 2014" <<std::endl;
		std::cout<<"Integrantes: Alvarez Etcheverry Florencia, Atadia Javier, Tierno Jonathan" <<std::endl;
		std::cout<<"Parametros: "<<std::endl;
		std::cout<<"	-h :mostrar esta ayuda"<<std::endl;
		std::cout<<"	-d : generar log de debug"<<std::endl;
		std::cout<<"	-v numero : duracion de la vuelta (Obligatorio >0)"<<std::endl;
		std::cout<<"	-p numero : precio del boleto (Obligatorio >= 0)"<<std::endl;
		std::cout<<"	-a numero : cantidad de asientos (Obligatorio > 0)"<<std::endl;
		std::cout<<"	-n numero : cantidad de ninios (Opcional > 0)"<<std::endl;
		std::cout<<"	-m numero : cantidad de plata que poseen los ninios (Opcional >= 0)"<<std::endl;
		std::cout<<"Si se ingresan numeros opcionales invalidos se elgiran por el programa"<<std::endl;
		return 0;
	}
	found=false;

	int duracionVuelta = getParamInt(argc,argv,"-v",found);
	if (!found || duracionVuelta==0){std::cout<<"El parametro: -v es obligatorio. ver ayuda -h para detalles"<<std::endl;return -1;}

	int precioBoleto = getParamInt(argc,argv,"-p",found);
	if (!found){std::cout<<"El parametro: -p es obligatorio. ver ayuda -h para detalles"<<std::endl;return -1;}

	int cantidadAsientos = getParamInt(argc,argv,"-a",found);
	if (!found || cantidadAsientos==0){std::cout<<"El parametro: -a es obligatorio. ver ayuda -h para detalles"<<std::endl;return -1;}

	bool debug = getParam(argc,argv,"-d");

	int ninios = getParamInt(argc,argv,"-n",found);
	if ((!found) || ninios==0){ninios=calcular_random(MIN_NINIOS,MAX_NINIOS);}

	int plataNinios=getParamInt(argc,argv,"-m",found);
	if ((!found)){plataNinios=10;}

	list<int> pids;


	try{

		//---------------INICIALIZANDO LOGGER--------------------
		Parametros paramsLogger;
		if(debug){
			paramsLogger.push("-d");
			paramsLogger.push(DEFAULT_LOG_FILE);
		}
		Proceso logger(EJECUTABLE_LOGGER,paramsLogger);
		Logger log("MAESTRO");
		log.log("Iniciado proceso del LOGGER con PID <0>",1, logger.getPid());
		pids.push_back(logger.getPid());


		//---INICIALIZO LA MEMORIA COMPARTIDA DE LOS ASIENTOS DE LA CALESITA---
		try{
		Asientos calesita_asientos(cantidadAsientos);
		} catch (MemoriaCompartidaException &e) { //Si no se pudo crear, mato al logger y vuelvo
			log.log("Error al crear los asientos de la calesita."+e.what());
			kill(QUIT_SIGNAL,logger.getPid());
			return -1;
		}


		//---------------INICIALIZANDO GENERADOR DE NINIOS--------------------
		Parametros paramsGen;
		paramsGen.push(ninios);
		paramsGen.push(cantidadAsientos);
		paramsGen.push(plataNinios);
		Proceso generador(EJECUTABLE_GENERADOR,paramsGen,&log);
		log.log("Iniciado proceso del GENERADOR con PID <0>",1, generador.getPid());


		pids.push_back(generador.getPid());

		//---------------INICIALIZANDO CAJERO--------------------
		Parametros paramsCajero;
		paramsCajero.push(precioBoleto);
		Proceso cajero(EJECUTABLE_CAJERO,paramsCajero,&log);
		log.log("Iniciado proceso del CAJERO con PID <0>",1, cajero.getPid());
		pids.push_back(cajero.getPid());


		//---------------INICIALIZANDO CALESITA--------------------
		Parametros paramsCalesita;

		paramsCalesita.push(cantidadAsientos);
		paramsCalesita.push(duracionVuelta);
		Proceso calesita(EJECUTABLE_CALESITA,paramsCalesita,&log);
		log.log("Iniciado proceso del CALESITA con PID <0>",1, calesita.getPid());
		pids.push_back(calesita.getPid());

		//---------------INICIALIZANDO ADMINISTRADOR--------------------
		Proceso admin(EJECUTABLE_ADMINISTRADOR,&log);
		log.log("Iniciado proceso del ADMINISTRADOR con PID <0>",1, admin.getPid());
		pids.push_back(admin.getPid());


		//esperando que los ninios terminen

		waitpid(generador.getPid(),NULL,0);
		log.log("Termino el generador");
		
		//una vez que los niños terminan cerramos todos los procesos

		kill(cajero.getPid(),QUIT_SIGNAL);
		log.log("Esperando que el cajero termine");
		waitpid(cajero.getPid(),NULL,0);

		kill(calesita.getPid(),QUIT_SIGNAL);
		log.log("Esperando que la calesita termine");
		waitpid(calesita.getPid(),NULL,0);

		kill(admin.getPid(),QUIT_SIGNAL);
		log.log("Esperando que el administrador termine");
		waitpid(admin.getPid(),NULL,0);

		log.log("Apagando logger y terminando programa");
		log.end();
		waitpid(logger.getPid(),NULL,0);
		
		//eliminamos los archivos temporales que se generaron de los locks
		unlink(LOCK_ENTRADA.c_str());
		unlink(LOCK_SALIDA.c_str());
		unlink(LOCK_ASIENTOS.c_str());
		unlink(LOCK_CAJA.c_str());

		std::cout<<"Programa terminado correctamente"<<std::endl;

	} catch (ProcesoException & e) {
		std::cout<<"La simulación no pudo comenzar. No se pudideron correr todos los procesos: "<<e.what()<<endl;
		list<int>::iterator it;
		for(it = pids.begin(); it != pids.end(); ++it){
			kill(QUIT_SIGNAL,*it);

		}
	}catch (Exception & e) {
		std::cout<<"La simulacion no pudo comenzar. No se pudideron correr todos los procesos: "<<e.what()<<endl;
	}catch(...){
		std::cout<<"Error desconocido"<<endl;
	}

}
