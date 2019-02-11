#include "LoginServer.h"
#include "../../client/Client.h"
#include "../../Master.h"

#include <iterator>
#include <mutex>
#include <poll.h>
#include <algorithm>
#include <memory>
#include <iostream>


LoginServer::LoginServer(char* ip, int port, std::shared_ptr<Master> master, int id) : GenericMapleServer(ip, port, master, id)
{
	std::cout << "LoginServer constructor called" << '\n';
}

LoginServer::~LoginServer()
{
	std::cout << "LoginServer destructor called" << '\n';
}

bool LoginServer::run()
{
	std::cout << "LoginServer running" << '\n';
//	std::cout << "Server ID: " << this->getID() << '\n';
//	std::shared_ptr<std::thread> loginWorkerThread;
//	std::shared_ptr<Client> client(new Client());
/*
	while(true)
	{	
		if(this->getMaster().get()->serverAlertQueue.get()->size() > 0)
		{
			std::lock_guard<std::mutex> lock(this->getMaster()->mutex);
			if(!this->getMaster().get()->checkChannelsOnline())
			{
				std::cout << "Shutting down login server" << '\n';
				this->alertServer(1);
				break;
			}
		}

		sockaddr_in client_addr;
		socklen_t clientSize = sizeof(client_addr);

		struct pollfd *fds;
		int fdcount = this->getConnectionsLength() + 1;
		fds = (pollfd*)malloc(sizeof(struct pollfd) * fdcount);

		fds[0].fd = this->getSocket();
		fds[0].events = POLLOUT | POLLIN;

		int j = 0;
		Connections temp = this->getConnections();
		std::for_each(temp.get()->begin(), temp.get()->end(), [&temp, &fds, &j](auto connection) 
		{
			fds[j + 1].fd = temp.get()->at(connection.first)->getSocket()->getSocket();
			fds[j + 1].events = POLLOUT | POLLIN;
		});
		if(poll(fds, fdcount, this->POLL_TIMEOUT))
		{
			client->setSocket(accept(this->getSocket(),
					         (sockaddr*) &client_addr, 						   &clientSize));
		}

		if(client->getSocket()->getSocket() != -1 && client->getSocket() != 0)
		{
			// Spawn client on new thread
		//	std::cout << "Client connected" << '\n';
		
			loginWorkerThread = std::thread([=]
			{ 
				this->spawnWorker(client); 
			});
		//	this->addConnection(client, loginWorkerThread);
		}
		free(fds);
	}

	//std::for_each(this->getConnections()->begin(), this->getConnections()->end(), [](auto connection)
	//{
	//	connection.second.get()->join();
	//});
	
*/
//	this->disconnect();
	std::cout << "Login server shutting down" << '\n';
	return true;
}

bool LoginServer::connect()
{
	return true;
}

bool LoginServer::disconnect()
{
	this->setStatus(OFFLINE);
	return true;
}

bool LoginServer::reconnect()
{
	return true;
}

bool LoginServer::alertServer(int command)
{
	std::lock_guard<std::mutex> lock(*(this->getMutex()));
	try
	{	
		auto sp = this->getServerAlertQueue().lock();
		sp.get()->push(1);
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception caught alerting server" << '\n';
	}
	return true;
}

bool LoginServer::spawnWorker(std::shared_ptr<Client> client)
{
	LoginWorker loginWorker = LoginWorker(std::shared_ptr<LoginServer>(this), client);
	loginWorker.run();
	return true;
}


