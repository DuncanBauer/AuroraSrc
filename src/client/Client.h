#ifndef CLIENT_H
#define CLIENT_H

#include "../net/sockets/TCPSocket.h"

class Client
{
	public:
		Client();
		Client(TCPSocket* sock);
		~Client();

		int getSocket();
		void setSocket(int sock);

	protected:
		TCPSocket* sock;
};


#endif
