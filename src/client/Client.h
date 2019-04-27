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

		int getSocket();
		void setSocket(int sock);
		
		sockaddr_in* getHint();
		void setHint(sockaddr_in client_addr);

		void disconnect();

	protected:
		std::shared_ptr<TCPSocket> sock;
};


#endif
