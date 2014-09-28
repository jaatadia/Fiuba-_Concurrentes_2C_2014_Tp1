#ifndef FIFO_H_
#define FIFO_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../lock/Lock.h"
class Fifo {
public:
	Fifo(const std::string nombre);
	Fifo(const std::string nombre, Lock * lock);
	virtual ~Fifo();
	virtual void abrir() = 0;
	void getLock();
	void unlock();
	void cerrar();
	void eliminar() const;

protected:
	std::string nombre;
	int fd;
	Lock * lock;
};

#endif /* FIFO_H_ */
