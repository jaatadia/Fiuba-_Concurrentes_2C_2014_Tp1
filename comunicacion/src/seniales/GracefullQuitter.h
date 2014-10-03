#ifndef GRACEFULLQUITTER_H_
#define GRACEFULLQUITTER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

class GracefullQuitter : public EventHandler {

	private:
		sig_atomic_t gracefulQuit;

	public:

		GracefullQuitter () : gracefulQuit(0) {
		}

		~GracefullQuitter () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGINT );
			this->gracefulQuit = 1;
			return 0;
		}

		sig_atomic_t alive () const {
			return this->gracefulQuit;
		}

};

#endif /* GRACEFULLQUITTER_H_ */
