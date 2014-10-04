#ifndef INTERRUPTER_H_
#define INTERRUPTER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

class Interrupter : public EventHandler {

	private:
		sig_atomic_t interrupt;

	public:

		Interrupter () : interrupt(0) {
		}

		~Interrupter () {
		}

		virtual int handleSignal ( int signum ) {
			return 0;
		}



};

#endif /* INTERRUPTER_H_ */
