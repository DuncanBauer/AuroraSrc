#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>


class TCPSocket 
{
	public:
        	TCPSocket();
		TCPSocket(int sock);
        	~TCPSocket();

		void setSocket(int sock);
		int getSocket();

		sockaddr_in hint; // Socket info

	private:
		int sock; // Socket the user is connected to
};

#endif
