#include "TCPServerSocket.h"
#include "../../client/Client.h"

#include <iterator>
#include <poll.h>
#include <algorithm>
#include <memory>
#include <iostream>


TCPServerSocket::TCPServerSocket(char* ip, int port, int id)
{
//	std::cout << "TCPServerSocket constructor called" << '\n';
	this->setStatus(OFFLINE);
	if(this->initialize(ip, port))
	{	
		std::cout << "Server Online \n";
	}
	this->connections.reset(new Connections());
	this->setID(id);
}

TCPServerSocket::~TCPServerSocket()
{
//	std::cout << "TCPServerSocket destructor called" << '\n';
	try
	{
		if(!this->connections.get()->empty())
		{
			this->connections.get()->clear();
		}
		this->connections.reset();
		close(this->getSocket());
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception thrown in TCPSocketServer destructor" << '\n';
	}
	std::cout << "Destruction complete" << '\n';
}

bool TCPServerSocket::initialize(char* address, int port)
{
	this->setStatus(INITIALIZING);
	this->setSocket(socket(AF_INET, SOCK_STREAM, 0));
	if(this->getSocket() == -1)
	{
		std::cerr << "Can\'t create socket" << '\n';
		return -1;
	}

	this->hint.sin_family = AF_INET;
	this->hint.sin_port = htons(port);
	inet_pton(AF_INET, address, &(this->hint.sin_addr));

	if(bind(this->getSocket(), (sockaddr*)&(this->hint), sizeof(this->hint)) == -1)
	{
		std::cerr << "Couldn\'t bind socket to IP/PORT" << '\n';
		this->setStatus(OFFLINE);
		return false;
	}

	if(listen(this->getSocket(), SOMAXCONN) == -1)
	{
		std::cerr << "Can\'t listen" << '\n';
		this->setStatus(OFFLINE);
		return false;
	}

	this->setStatus(ONLINE);
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

bool TCPServerSocket::spawnWorker(std::shared_ptr<Client> client)
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

int TCPServerSocket::getConnectionsLength()
{
	return this->connections->size();
}

void TCPServerSocket::addConnection(std::shared_ptr<Client> client, std::thread &thread)
{
	this->connections.get()->emplace(client, thread);
}

void TCPServerSocket::removeConnection(std::shared_ptr<Client> client)
{
	try
	{
		this->connections->erase(client);
	}
	catch(...)
	{
		std::cerr << "No connections to remove" << '\n';
	}
}

Connections* TCPServerSocket::getConnections()
{
	return this->connections.get();
}
