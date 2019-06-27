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
}

bool TCPClientSocket::closeSocket()
{
	return true;
}

void TCPClientSocket::disconnect()
{
}
