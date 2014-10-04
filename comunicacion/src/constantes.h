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

//PATHS
static const string MAIN_FOLDER = "/home/jonathan/git/Fiuba-_Concurrentes_2C_2014_Tp1/";
static const string DEBUG="/Debug";
static const string EJECUTABLE_CAJERO = MAIN_FOLDER + "/cajero_p" + DEBUG+"/cajero_p";
static const string PATH_FIFOVENTA= "/tmp/venta-fifo";
static const string PATH_FIFOLOG = "/tmp/log-fifo";


//MENSAJES
static const string MENSAJE_VACIO= "v";
static const string MENSAJE_LOG= "l";
static const string MENSAJE_STRING= "s";
static const string MENSAJE_COMPRAVENTA= "c";

static const int NRO_BOLETO_INVALIDO=0;

#endif /* CONSTANTES_H_ */
