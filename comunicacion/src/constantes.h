/*
 * constantes.h
 *
 *  Created on: 25/9/2014
 *      Author: jonathan
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_
#include <string>
using namespace std;
static int const ERR_CODE=-1;

//PATHS; Definir la carpeta donde esta el ejecutable. Notar que las FOLDER_ no tienen espacios ni antes ni dsps del =, dejarlas asi.
static const string MAIN_FOLDER="/home/jonathan/git/Fiuba-_Concurrentes_2C_2014_Tp1";
static const string DEBUG="/Debug";
static const string FOLDER_CAJERO="/cajero_p";
static const string FOLDER_CALESITA="/calesita_p";
static const string FOLDER_GENERADOR="/generador_p";
static const string FOLDER_LOGGER="/logger_p";
static const string FOLDER_NINIO="/ninio_p";

//Se arman asi para dsps dinamicamente armar un release con bash.
static const string EJECUTABLE_CAJERO = MAIN_FOLDER + FOLDER_CAJERO + DEBUG+"/cajero_p";
static const string EJECUTABLE_CALESITA = MAIN_FOLDER + FOLDER_CALESITA + DEBUG+"/calesita_p";
static const string EJECUTABLE_GENERADOR = MAIN_FOLDER + FOLDER_GENERADOR + DEBUG+"/generador_p";
static const string EJECUTABLE_LOGGER = MAIN_FOLDER + FOLDER_LOGGER + DEBUG+"/logger_p";
static const string EJECUTABLE_NINIO = MAIN_FOLDER + FOLDER_NINIO + DEBUG+"/ninio_p";


static const string PATH_FIFOVENTA= "/tmp/venta-fifo";
static const string PATH_FIFOLOG = "/tmp/log-fifo";


//MENSAJES
static const string MENSAJE_VACIO= "v";
static const string MENSAJE_LOG= "l";
static const string MENSAJE_STRING= "s";
static const string MENSAJE_COMPRAVENTA= "c";

static const int NRO_BOLETO_INVALIDO=0;

#endif /* CONSTANTES_H_ */
