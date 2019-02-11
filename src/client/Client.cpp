#include "Client.h"

Client::Client()
{
	this->sock = std::shared_ptr<TCPSocket>(new TCPSocket());
}

Client::Client(TCPSocket* sock)
{
	this->sock = std::shared_ptr<TCPSocket>(sock);
}

Client::Client(std::shared_ptr<TCPSocket> sock)
{
	this->sock = sock;
}

Client::~Client()
{
	this->sock.reset();
}

std::shared_ptr<TCPSocket> Client::getSocket()
{
	return this->sock;
}

void Client::setSocket(int sock)
{
	this->sock.reset(new TCPSocket(sock));
}

void Client::disconnect()
{
	this->sock.reset();
}
