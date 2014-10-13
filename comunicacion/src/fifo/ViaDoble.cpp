/*
 * ViaDoble.cpp
 *
 *  Created on: 28/09/2014
 *      Author: jonathan
 */

#include "ViaDoble.h"
#include <iostream>

ViaDoble::ViaDoble(const string nombre, bool duenio): duenio(duenio), abierta(false), serializador(),out(nombre + "-" + (duenio ? OUT_POSTFIX : IN_POSTFIX),serializador),in(nombre + "-" + (duenio ? IN_POSTFIX : OUT_POSTFIX),serializador),inEsc(nombre + "-" + (duenio ? IN_POSTFIX : OUT_POSTFIX),serializador){
	this->abrir();
}

ViaDoble::~ViaDoble() {
	cerrar();
	if (duenio) {
		std::cout<<"Se eliminan cosas que no se deben"<<std::endl;
		this->in.eliminar();
		this->out.eliminar();
	}
}

void ViaDoble::enviar(Mensaje * mje) {
	this->out.escribir(mje);

}

Mensaje* ViaDoble::recibir() {
	return this->in.leer();
}

void ViaDoble::cerrar() {
	if(abierta){
		abierta = false;
		this->in.cerrar();
		this->out.cerrar();
		if(duenio){
			this->inEsc.cerrar();
		}
	}
}

void ViaDoble::abrir() {
	abierta = true;
	if (this->duenio) {
		this->in.abrir();
		this->inEsc.abrir();
		this->out.abrir();
	} else {
		this->out.abrir();
		this->in.abrir();
	}
}

string ViaDoble::getNombreEntrada() {
	if (this->duenio) {
		return this->in.getNombre();
	}
	return this->out.getNombre();
}
