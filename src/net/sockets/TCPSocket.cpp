#include "TCPSocket.h"

#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>


TCPSocket::TCPSocket() : sock(0)
{
	std::cout << "TCPSocket default constructor called" << '\n';
}

TCPSocket::TCPSocket(int sock) : sock(sock)
{
	std::cout << "TCPSocket constructor called" << '\n';
}

TCPSocket::~TCPSocket()
{
	std::cout << "TCPSocket destructor called" << '\n';
	try
	{
		close(this->sock);
	}
	catch(std::exception& ex)
	{
		std::cerr << "Exception thrown destroying TCPSocket" << '\n';
	}
}

void TCPSocket::setSocket(int sock)
{
	this->sock = sock;
}

int TCPSocket::getSocket()
{
	return this->sock;
}
