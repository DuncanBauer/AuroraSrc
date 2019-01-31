#ifndef TCPSocket_H
#define TCPSocket_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>

class TCPSocket 
{
    public:
        TCPSocket();
        ~TCPSocket();

	int initialize(char* address, int port);
	void setSocket(int sock);
	int getSocket();

    protected:
	int sock = 0;
	sockaddr_in hint;

    private:
};

#endif
