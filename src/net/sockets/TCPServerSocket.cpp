#include "TCPServerSocket.h"
#include "TCPClientSocket.h"

#include <sys/ioctl.h>
#include <iterator>
#include <poll.h>
#include <algorithm>
#include <memory>
#include <iostream>


TCPServerSocket::TCPServerSocket(char* ip, int port, int id)
{
	this->setStatus(OFFLINE);
	if(this->initialize(ip, port))
	{	
		this->setStatus(READY);
	}
	this->setID(id);
}

TCPServerSocket::~TCPServerSocket()
{
}

bool TCPServerSocket::initialize(char* address, int port)
{
	std::cout << "INITIALIZING SERVER\n";
	this->setStatus(INITIALIZING);
	this->setSocket(socket(AF_INET, SOCK_STREAM, 0));
	if(this->getSocket() < 0)
	{
		std::cerr << "Can\'t create socket\n";
		return false;
	}

	this->getHint()->sin_family = AF_INET;
	this->getHint()->sin_port = htons(port);
	inet_pton(AF_INET, address, &(this->getHint()->sin_addr));

	int on = 1;
	if(setsockopt(this->getSocket(), SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
	{
		std::cerr << "Couldn't set socket reusable\n";
		this->setStatus(OFFLINE);
		return false;
	}

	if(ioctl(this->getSocket(), FIONBIO, (char *)&on) < 0)
	{	
		std::cerr << "Couldn't set socket nonblocking\n";
		this->setStatus(OFFLINE);
		return false;
	}

	if(bind(this->getSocket(), (sockaddr*)(this->getHint()), sizeof(*this->getHint())) < 0)
	{
		std::cerr << "Couldn\'t bind socket to IP/PORT\n";
		this->setStatus(OFFLINE);
		return false;
	}

	if(listen(this->getSocket(), SOMAXCONN) < 0)
	{
		std::cerr << "Can\'t listen\n";
		this->setStatus(OFFLINE);
		return false;
	}

	return true;
}

bool TCPServerSocket::run()
{
/*  THIS IS HERE FOR REFERENCE
	while(true)
	{
		sockaddr_in client;
		socklen_t clientSize = sizeof(client);
	//	char host[NI_MAXHOST];
	//	char service[NI_MAXSERV];

		TCPSocket* clientSock = new TCPSocket();

		struct pollfd *fds;
		int fdcount = this->getConnectionsLength() + 1;
		fds = (pollfd*)malloc(sizeof(struct pollfd) * fdcount);
		fds[0].fd = this->getSocket();
		fds[0].events |= POLLOUT;
		
		for(int i = 0; i < this->getConnectionsLength(); ++i)
		{
			fds[i + 1].fd = this->getConnections()[i]->getSocket();
			fds[i + 1].events |= POLLOUT;
		}
		
		if(poll(fds, fdcount, this->POLL_TIMEOUT))
		{
			// CHECK POLLING RESULTS
			clientSock->setSocket(accept(this->getSocket(),
						     (sockaddr*) &client,
						     &clientSize));
	
			if(clientSock->getSocket() != -1 && clientSock->getSocket() != 0)
			{
			}
		}
		free(fds);
		delete clientSock;
	}

*/	return true;
}

bool TCPServerSocket::connect()
{
	return true;
}

bool TCPServerSocket::disconnect()
{
	return true;
}

bool TCPServerSocket::reconnect()
{
	return true;
}

bool TCPServerSocket::alertServer(int command)
{
	return true;
}

bool TCPServerSocket::spawnWorker(std::shared_ptr<TCPClientSocket> client)
{
	return true;
}

int TCPServerSocket::getID()
{
	return this->id;
}

void TCPServerSocket::setID(int id)
{
	this->id = id;
}

ServerStatus TCPServerSocket::getStatus()
{
	return this->status;
}

void TCPServerSocket::setStatus(ServerStatus status)
{
	this->status = status;
}

std::mutex* TCPServerSocket::getMutex()
{
	return &(this->mtx);
}
