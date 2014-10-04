#ifndef LOCKFILE_H_
#define LOCKFILE_H_

#include <unistd.h>
#include <fcntl.h>
#include <string>
/**
 * Clase que permite establecer un lock sobre un archivo.
 */
class LockFile {

private:
	struct flock fl;
	int fd;
	std::string nombre;

public:
	LockFile ( const std::string nombre );
	~LockFile();
	void tomarLock ();
	void liberarLock ();
//	ssize_t escribir ( const void* buffer,const ssize_t buffsize ) const;
};

#endif /* LOCKFILE_H_ */
