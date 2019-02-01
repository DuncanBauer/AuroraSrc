#ifndef LOGINSERVER_H
#define LOGINSERVER_H

/*
 * Included from TCPServerSocket.h
 *
 * #include "../packets/PacketHandler.h"
 * #include "TCPSocket.h"
 * #include <poll>
 * #include <vector>
 * #include <iterator>
 *
 */

#include "LoginWorker.h"
#include "../sockets/TCPServerSocket.h"

class LoginServer : public TCPServerSocket
{
	public:
		LoginServer();
		virtual ~LoginServer();
		
		virtual void run();

	private:
};


#endif
