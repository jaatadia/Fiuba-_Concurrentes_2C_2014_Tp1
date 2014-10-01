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
static const char MENSAJE_VACIO= 1;
static const char MENSAJE_LOG= 2;

#endif /* CONSTANTES_H_ */
