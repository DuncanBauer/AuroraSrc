#include "TCPClientSocket.h"

#include <cstdlib>
#include <iostream>

TCPClientSocket::TCPClientSocket()
{
}

TCPClientSocket::TCPClientSocket(int sock) : TCPSocket(sock)
{
}

TCPClientSocket::~TCPClientSocket()
{
	std::cout << "TCPClientSocket destructor called\n";
}

void TCPClientSocket::disconnect()
{
}
