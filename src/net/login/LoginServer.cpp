#include "LoginServer.h"
#include "../../client/Client.h"
#include "../../Master.h"

#include <iterator>
#include <mutex>
#include <poll.h>
#include <algorithm>
#include <memory>
#include <iostream>


LoginServer::LoginServer(char* ip, int port, Master* master, int id) : GenericMapleServer(ip, port, master, id)
{
	std::cout << "LoginServer constructor called" << '\n';
}

LoginServer::~LoginServer()
{
	std::cout << "LoginServer destructor called" << '\n';
}

bool LoginServer::run()
{
	// Run until shutdown command is sent
	while(true)
	{	
		// Reads and executes server commands
		if(this->getMaster()->serverAlertQueue->size() > 0)
		{
			std::cout << this->getMaster()->serverAlertQueue->size() << '\n';
			std::lock_guard<std::mutex> lock(this->getMaster()->mutex);
			//if(!this->getMaster()->checkChannelsOnline())
			//{
			std::cout << "Shutting down login server" << '\n';
				//this->alertServer(1);
			break;
			//}
		}

		// Set up for new connection
		sockaddr_in client_addr;
		socklen_t clientSize = sizeof(client_addr);

		std::thread loginWorkerThread;
		std::shared_ptr<Client> client(new Client());

		std::cout << "Connections length: " << this->getConnectionsLength() << '\n';
		
		struct pollfd *fds;
		int fdcount = this->getConnectionsLength() + 1;
		fds = (pollfd*)malloc(sizeof(struct pollfd) * fdcount);

		fds[0].fd = this->getSocket();
		fds[0].events = POLLIN | POLLOUT;
		//fds[0].events |= POLLOUT;

		int j = 0;
		Connections* temp = this->getConnections();
		// Checks for pending connections and connects the first one
		std::for_each(temp->begin(), temp->end(), [temp, &fds, &j](auto connection) 
		{
		//	fds[j + 1].fd = temp->at(connection.first)->getSocket()->getSocket();
			fds[j + 1].fd = connection.first->getSocket()->getSocket();
		//	fds[j + 1].events |= POLLOUT;
			fds[j + 1].events = POLLIN | POLLOUT;
			j++;
		});

		std::cout << "HANG?\n";
		
		if(poll(fds, fdcount, this->POLL_TIMEOUT))
		{
			client->setSocket(accept(this->getSocket(),
					         (sockaddr*) &client_addr, 
						 &clientSize));

			std::cout << "Socket: " << client->getSocket().get()->getSocket() << '\n';
	
			if(client->getSocket().get()->getSocket() != -1 && client->getSocket().get()->getSocket() != 0)
			{
				// Spawn client on new thread
				std::cout << "Client connected" << '\n';
			
				loginWorkerThread = std::thread([=]
				{ 
					this->spawnWorker(client); 
				});
				this->addConnection(client, loginWorkerThread);
			}
		}
		
		std::cout << client->getSocket().get()->getSocket() << '\n';
/*
		if(client->getSocket().get()->getSocket() != -1 && client->getSocket().get()->getSocket() != 0)
	//	if(client->getSocket().get()->getSocket() >= 0)
		{
			std::cout << client->getSocket()->getSocket() << '\n';
			// Spawn client on new thread
			std::cout << "Client connected" << '\n';
		
			loginWorkerThread = std::thread([=]
			{ 
				this->spawnWorker(client); 
			});
			this->addConnection(client, loginWorkerThread);
		}
*/
		free(fds);
	}

	std::for_each(this->getConnections()->begin(), this->getConnections()->end(), [](auto connection)
	{
		connection.second.join();
	});
	
	this->disconnect();
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
		this->serverAlertQueue->push(command);
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception caught alerting server" << '\n';
	}
	return true;
}

bool LoginServer::spawnWorker(std::shared_ptr<Client> client)
{
	LoginWorker loginWorker = LoginWorker(this, client);
//	workers.get()->emplace(workers.get()->size(), std::make_shared<LoginWorker>(loginWorker));
//	loginWorker.run();
	return true;
}


