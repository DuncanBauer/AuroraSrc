#include "TCPSocket.h"

#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>


TCPSocket::TCPSocket() : sock(0)
{
//	std::cout << "TCPSocket default constructor called" << '\n';
}

TCPSocket::TCPSocket(int sock) : sock(sock)
{
//	std::cout << "TCPSocket constructor called" << '\n';
}

TCPSocket::~TCPSocket()
{
//	std::cout << "TCPSocket destructor called" << '\n';
	try
	{
		if(!this->closeSocket())
		{
			std::cerr << "TCPSocket failed to close\n";
		}
	}
	catch(std::exception& ex)
	{
		std::cerr << "Exception thrown destroying TCPSocket" << '\n';
	}
}

bool TCPSocket::closeSocket()
{
	if(sock > -1)
	{
		close(this->sock);
		return true;
	}
	return false;
}

void TCPSocket::setSocket(int sock)
{
	this->sock = sock;
}

int TCPSocket::getSocket()
{
	return this->sock;
}

sockaddr_in* TCPSocket::getHint()
{
	return &(this->hint);
}

void TCPSocket::setHint(sockaddr_in client_addr)
{
	this->hint = client_addr;
}


