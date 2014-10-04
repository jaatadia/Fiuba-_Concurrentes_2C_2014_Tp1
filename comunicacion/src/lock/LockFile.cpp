#include "LockFile.h"

#include <errno.h>
#include <string.h>

#include "LockException.h"
#include "../constantes.h"

LockFile::LockFile(const std::string nombre) {

	this->nombre = nombre;
	this->fl.l_type = F_WRLCK;
	this->fl.l_whence = SEEK_SET;
	this->fl.l_start = 0;
	this->fl.l_len = 0;
	this->fd = open(this->nombre.c_str(), O_CREAT | O_WRONLY, 0777);
	if (fd == ERR_CODE) {
		throw LockException("No se pudo abrir el archivo para lockear",
				strerror(errno));
	}
}

void LockFile::tomarLock() {
	this->fl.l_type = F_WRLCK;
	int rslt = fcntl(this->fd, F_SETLKW, &(this->fl));
	if (rslt == ERR_CODE) {
		throw LockException("No se pudo tomar el lock", strerror(errno));
	}

}

void LockFile::liberarLock() {
	this->fl.l_type = F_UNLCK;
	int rslt = fcntl(this->fd, F_SETLK, &(this->fl));
	if (rslt == ERR_CODE) {
		throw LockException("No se pudo liberar el lock", strerror(errno));
	}
}

//ssize_t LockFile :: escribir ( const void* buffer,const ssize_t buffsize ) const {
//	lseek ( this->fd,0,SEEK_END );
//	return write ( this->fd,buffer,buffsize );
//}

LockFile::~LockFile() {
	close(this->fd);
}
