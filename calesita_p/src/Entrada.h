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

class Entrada {
public:
	Entrada(int nroNinos);//recibe la cantidad de niños que pueden ingresar a la vez
	void reset();//se resetean los valores internos
	int proxNino();//espera al proximio niño, devuele 1 en caso de que la espera fue exitosa; -1 en caso de que sea posible esperar
	int huboError();//devuelve si hubo error (error para salir del programa)
	void liberar();//libera los niños que entraron

	virtual ~Entrada();
private:
	int inicial();//devuelve 1 si llega el nino ; -1 en caso de error
	int proximo();//devuelve 1 si llega el nino ; devuelve 0 si no llego el proximo niño despues de timeout ; -1 en caso de error
	int tramitarNino(Mensaje* msj);
	Mensaje* getBoleto();//devuelve el boleto o NULL si no pudo obtenerlo
	void esperarSentado();//espera a que el niño se siente

	//falta implementar
	int verificarBoleto(Mensaje* boleto);//devuelve 1 si el voleto es balido , -1 sino

	int comenzarVuelta;
	int error;
	int ninos;//cantidad de niños que espere
	int nroNinosPorVuelta;//cantidad de ninos por vuelta
	int nroNinosEnVuelta;//la cantidad de niños que hay
	Serializador ser;
	FifoLectura fifoLec;
	FifoEscritura fifoEsc;
	FifoEscritura fifoTimeout;
};

#endif /* ENTRADA_H_ */
