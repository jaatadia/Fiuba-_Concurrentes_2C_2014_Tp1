/*
 * constantes.h
 *
 *  Created on: 25/9/2014
 *      Author: jonathan
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_
#include <string>
#include <sys/wait.h>
using namespace std;
static int const ERR_CODE=-1;


//generales
static const string DEFAULT_LOG_FILE="./calesita.log";


//PATHS; Definir la carpeta donde esta el ejecutable. Notar que las FOLDER_ no tienen espacios ni antes ni dsps del =, dejarlas asi.
static const string MAIN_FOLDER="/home/jonathan/git/Fiuba-_Concurrentes_2C_2014_Tp1";
static const string DEBUG="/Debug";
static const string FOLDER_CAJERO="/cajero_p";
static const string FOLDER_CALESITA="/calesita_p";
static const string FOLDER_GENERADOR="/generador_p";
static const string FOLDER_LOGGER="/logger_p";
static const string FOLDER_NINIO="/ninio_p";

//Se arman asi para dsps dinamicamente armar un release con bash.
/*static const string EJECUTABLE_CAJERO = MAIN_FOLDER + FOLDER_CAJERO + DEBUG+"/cajero_p";
static const string EJECUTABLE_CALESITA = MAIN_FOLDER + FOLDER_CALESITA + DEBUG+"/calesita_p";
static const string EJECUTABLE_GENERADOR = MAIN_FOLDER + FOLDER_GENERADOR + DEBUG+"/generador_p";
static const string EJECUTABLE_LOGGER = MAIN_FOLDER + FOLDER_LOGGER + DEBUG+"/logger_p";
static const string EJECUTABLE_NINIO = MAIN_FOLDER + FOLDER_NINIO + DEBUG+"/ninio_p";*/
static const string EJECUTABLE_CAJERO = "./cajero_p";
static const string EJECUTABLE_CALESITA = "./calesita_p";
static const string EJECUTABLE_GENERADOR = "./generador_p";
static const string EJECUTABLE_LOGGER = "./logger_p";
static const string EJECUTABLE_NINIO = "./ninio_p";
static const string EJECUTABLE_ADMINISTRADOR = "./administrador_p";

//cajero
static const string PATH_FIFOVENTA= "/tmp/venta-fifo";
static const string PATH_FIFOLOG = "/tmp/log-fifo";
static const int NRO_BOLETO_INVALIDO=0;


//MENSAJES
static const string MENSAJE_VACIO= "v";
static const string MENSAJE_LOG= "l";
static const string MENSAJE_STRING= "s";
static const string MENSAJE_COMPRAVENTA= "c";
static const string MENSAJE_NUMERO= "n";

//SENIALES
static const pid_t QUIT_SIGNAL = SIGUSR1;
static const pid_t ERROR_SIGNAL = SIGUSR2;

//calesita
static const string PATH_FIFO_CALESITA_HACIA_CALESITA="/tmp/fifo_calesita";
static const string PATH_FIFO_CALESITA_HACIA_NINOS="/tmp/fifo_calesita_ninos";
static const string PATH_FIFO_CALESITA_TIMEOUT="/tmp/fifo_calesita_timeout";
static const string LOCK_ENTRADA="/tmp/lock_entrada.tmp";
static const string LOCK_SALIDA="/tmp/lock_salida.tmp";
static const string LOCK_ASIENTOS="/tmp/lock_asientos.tmp";
static const int CALESITA_TIMEOUT=5;
static const int CALESITA_PASAR=0;
static const int CALESITA_NO_PASAR=1;

//semaforo
static const string PATH_ARCH_SEM_ASIENTOS="/tmp/fifo_calesita";
static const string PATH_ARCH_SEM_CALE="/tmp/fifo_calesita_ninos";

//memoria compartida
static const string MEMCOMP_ARCH=LOCK_ASIENTOS; //TODO qué archivo usar? y que letra?
static const char MEMCOMP_LETRA='a';

//caja (lock)
static const string LOCK_CAJA="/tmp/lock_caja.tmp";

//nro max para random
static const int MAX_ADMIN_DORMIR=10;
static const int MAX_NINIO_RND=333;

//ninios
static const int MIN_NINIOS=1;
static const int MAX_NINIOS=5;


#endif /* CONSTANTES_H_ */
