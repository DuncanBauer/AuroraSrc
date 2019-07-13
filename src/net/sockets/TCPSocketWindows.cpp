#include "TCPSocketWindows.h"


TCPSocketWindows::TCPSocketWindows() : sock(0)
{
//	std::cout << "TCPSocketWindows default constructor called" << '\n';
    ZeroMemory(&this->hint, sizeof (this->hint));
    this->hint.ai_family = AF_INET;
    this->hint.ai_socktype = SOCK_STREAM;
    this->hint.ai_protocol = IPPROTO_TCP;
    this->hint.ai_flags = AI_PASSIVE;
}

TCPSocketWindows::TCPSocketWindows(int sock) : sock(sock)
{
//	std::cout << "TCPSocketWindows constructor called" << '\n';
    ZeroMemory(&this->hint, sizeof (this->hint));
    this->hint.ai_family = AF_INET;
    this->hint.ai_socktype = SOCK_STREAM;
    this->hint.ai_protocol = IPPROTO_TCP;
    this->hint.ai_flags = AI_PASSIVE;
}

TCPSocketWindows::~TCPSocketWindows()
{
//	std::cout << "TCPSocketWindows destructor called" << '\n';
	try
	{
		if(!this->closeSocket())
		{
			std::cerr << "TCPSocketWindows failed to close\n";
		}
	}
	catch(std::exception& ex)
	{
		std::cerr << "Exception thrown destroying TCPSocketWindows" << '\n';
	}
}

bool TCPSocketWindows::closeSocket()
{
	if(sock > -1)
	{
		//close(this->sock);
		return true;
	}
	return false;
}

void TCPSocketWindows::setSocket(int sock)
{
	this->sock = sock;
}

int TCPSocketWindows::getSocket()
{
	return this->sock;
}

addrinfo* TCPSocketWindows::getHint()
{
	return &(this->hint);
}

void TCPSocketWindows::setHint(addrinfo client_addr)
{
	this->hint = client_addr;
}
