#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <memory>


class TCPSocket
{
	public:
        TCPSocket();
		TCPSocket(int sock);
        ~TCPSocket();

		bool closeSocket();

		void setSocket(int sock);
		int getSocket();

		sockaddr_in* getHint();
		void setHint(sockaddr_in client_addr);


	private:
		int sock; // Socket the user is connected to
		sockaddr_in hint; // Socket info
};

#endif
