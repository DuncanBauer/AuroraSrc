#ifndef CLIENT_H
#define CLIENT_H

#include "../net/sockets/TCPSocket.h"

class LoginWorker;
class ChannelWorker;

class Client
{
	public:
		Client();
		Client(TCPSocket* sock);
		Client(std::shared_ptr<TCPSocket> sock);
		~Client();

		std::shared_ptr<TCPSocket> getSocket();
		void setSocket(int sock);

		void disconnect();

	protected:
		std::shared_ptr<TCPSocket> sock;
};


#endif
