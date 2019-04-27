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

int Client::getSocket()
{
	return this->sock.get()->getSocket();
}

void Client::setSocket(int sock)
{
	this->sock.reset(new TCPSocket(sock));
}

sockaddr_in* Client::getHint()
{
	return &(this->sock.get()->hint);
}

void Client::setHint(sockaddr_in client_addr)
{
	this->sock.get()->hint = client_addr;
}

void Client::disconnect()
{
	this->sock.reset();
}
