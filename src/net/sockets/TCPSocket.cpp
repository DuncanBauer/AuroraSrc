#include "TCPSocket.h"

TCPSocket::TCPSocket()
{
	this->sock = 0;
}

TCPSocket::~TCPSocket()
{
	if(this->sock > 0)
	{
		close(this->sock);
	}
}

int TCPSocket::initialize(char* address, int port)
{
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if(this->sock == -1)
	{
		std::cerr << "Can\'t create socket" << '\n';
		return -1;
	}

	this->hint.sin_family = AF_INET;
	this->hint.sin_port = htons(port);
	inet_pton(AF_INET, address, &(this->hint.sin_addr));

	if(bind(this->sock, (sockaddr*)&(this->hint), sizeof(this->hint)) == -1)
	{
		std::cerr << "Couldn\'t bind socket to IP/PORT" << '\n';
		return -2;
	}

	if(listen(this->sock, SOMAXCONN) == -1)
	{
		std::cerr << "Can\'t listen" << '\n';
		return -3;
	}

	return 1;
}

void TCPSocket::setSocket(int _sock)
{
	this->sock = _sock;
}

int TCPSocket::getSocket()
{
	return this->sock;
}
