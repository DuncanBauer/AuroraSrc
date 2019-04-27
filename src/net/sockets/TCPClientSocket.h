#ifndef CLIENT_H
#define CLIENT_H

#include "TCPSocket.h"

class LoginWorker;
class ChannelWorker;

class TCPClientSocket : public TCPSocket
{
	public:
		TCPClientSocket();
		TCPClientSocket(int sock);
		~TCPClientSocket();

		void disconnect();
};


#endif
