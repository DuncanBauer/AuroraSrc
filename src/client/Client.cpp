#include "Client.h"

Client::Client()
{
}

Client::Client(TCPSocket* sock)
{
	this->sock = sock;
}

Client::~Client()
{
	if(this->sock != nullptr)
	{
		delete this->sock;
	}
}

int Client::getSocket()
{
	return this->sock->getSocket();
}

void Client::setSocket(int sock)
{
	this->sock->setSocket(sock);
}
