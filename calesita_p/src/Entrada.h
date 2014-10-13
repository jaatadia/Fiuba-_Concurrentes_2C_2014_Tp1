/*
 * Entrada.h
 *
 *  Created on: Oct 7, 2014
 *      Author: javier
 */

#ifndef ENTRADA_H_
#define ENTRADA_H_

#include "src/constantes.h"
#include "src/fifo/FifoEscritura.h"
#include "src/fifo/FifoLectura.h"
#include "src/transferencia/Serializador.h"
#include "src/transferencia/Mensaje.h"
#include "src/transferencia/MensajeInt.h"
#include "src/logger/Logger.h"
#include "src/semaforos/Semaforo.h"
#include "src/seniales/GracefullQuitter.h"
#include "src/Exception.h"

class Entrada {
public:
	Entrada(int nroNinos, int vuelta, Logger* log,GracefullQuitter* quitter);//recibe la cantidad de niños que pueden ingresar a la vez
	void reset();//se resetean los valores internos
	int proximo();//espera al proximio niño
	void esperarSienten();//espera a que los niños se sienten
	void comenzarVuelta();//comienza la vuelta
	void liberar();//libera los niños que entraron
	int huboError();//devuelve si hubo error (error para salir del programa)
	bool estaVacia();
	bool estaLlena();
	virtual ~Entrada();

private:
	Mensaje* getBoleto();//devuelve el boleto o NULL si no pudo obtenerlo
/*TODO*/	int verificarBoleto(Mensaje* boleto);//devuelve 1 si el voleto es balido , -1 sino
	int tramitarNino(Mensaje* msj);



	int error;
	int vuelta;
	int ninos;//cantidad de niños que espere
	int nroNinosPorVuelta;//cantidad de ninos por vuelta
	int nroNinosEnVuelta;//la cantidad de niños que hay
	Serializador ser;
	FifoLectura fifoLec;//fifo para leer desde los niños
	FifoEscritura fifoLecEsc;//fifo para leer abierto para escritura para que no devuelva 0
	FifoEscritura fifoEsc;//fifo para escribir hacia los niños
	Logger* log;
	Semaforo semAsientosOcupados; //debe inicializarse en 0 asientos ocupados , para saber que se liberaron los ninos que necesitaba
	Semaforo semSoltarNinos;	//debe inicializarse 0 para yo liberar los ninos
	GracefullQuitter* quitter;
};

#endif /* ENTRADA_H_ */
