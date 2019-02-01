#include "TCPServerSocket.h"

TCPServerSocket::TCPServerSocket()
{
}

TCPServerSocket::~TCPServerSocket()
{
	this->connections.clear();
	close(this->sock);
}

void TCPServerSocket::run()
{
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

		// Handle connected clients here
		// check if theyre alive
		// disconnect if dead after certain amount of time
		// remove socket from connection vector
	}
}

int TCPServerSocket::getConnectionsLength()
{
	return this->connections.size();
}

void TCPServerSocket::addConnection(Client* client)
{
	this->connections.push_back(client);
}

void TCPServerSocket::removeConnection(Client* client)
{
	auto it = this->connections.begin();
	while(it != this->connections.end())
	{
		if((*it)->getSocket() == client->getSocket())
		{
			break;
		}
		std::next(it);
	}
	if(it == this->connections.end())
	{
		this->connections.erase(it);
	}
}


std::vector<Client*> TCPServerSocket::getConnections()
{
	return this->connections;
}

void TCPServerSocket::pruneConnections()
{
	for(auto it = this->connections.begin(); it != this->connections.end(); ++it)
	{
		//if(it == 0 || it == -1)

	}
}
