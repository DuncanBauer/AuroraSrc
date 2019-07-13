#ifndef TCPSOCKETWINDOWS_H
#define TCPSOCKETWINDOWS_H

//#include <sys/types.h>
//#include <sys/time.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <arpa/inet.h>
//#include <sys/socket.h>
#include <winsock2.h>
#include <memory>
#include <ws2tcpip.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <windows.h>
#include <stdio.h>


class TCPSocketWindows
{
	public:
        TCPSocketWindows();
		TCPSocketWindows(int sock);
        ~TCPSocketWindows();

		bool closeSocket();

		void setSocket(int sock);
		int getSocket();

		addrinfo* getHint();
		void setHint(addrinfo client_addr);


	private:
		int sock; // Socket the user is connected to
        struct addrinfo hint;
};

#endif
