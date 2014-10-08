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

class Entrada {
public:
	Entrada(int nroNinos, int vuelta, Logger* log);//recibe la cantidad de niños que pueden ingresar a la vez
	void reset();//se resetean los valores internos
	int proxNino();//espera al proximio niño, devuele 1 en caso de que la espera fue exitosa; -1 en caso de que sea posible esperar
	void esperarSienten();//espera a que los niños se sienten
	void comenzarVuelta();//comienza la vuelta
	void liberar();//libera los niños que entraron
	int huboError();//devuelve si hubo error (error para salir del programa)

	virtual ~Entrada();
private:
	int inicial();//devuelve 1 si llega el nino ; -1 en caso de error
	int proximo();//devuelve 1 si llega el nino ; devuelve 0 si no llego el proximo niño despues de timeout ; -1 en caso de error
	Mensaje* getBoleto();//devuelve el boleto o NULL si no pudo obtenerlo
/*falta*/	int verificarBoleto(Mensaje* boleto);//devuelve 1 si el voleto es balido , -1 sino
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
	FifoEscritura fifoTimeout;//fifo para escribir hacia el interrupter
	Logger* log;
	Semaforo semAsientosOcupados; //debe inicializarse en 0 asientos ocupados , para saber que se liberaron los ninos que necesitaba
	Semaforo semSoltarNinos;	//debe inicializarse 0 para yo liberar los ninos
};

#endif /* ENTRADA_H_ */
