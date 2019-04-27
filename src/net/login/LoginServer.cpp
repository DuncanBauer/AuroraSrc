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
//	std::cout << "LoginServer constructor called" << '\n';
}

LoginServer::~LoginServer()
{
//	std::cout << "LoginServer destructor called" << '\n';
}

bool LoginServer::run()
{
	// Run until shutdown command is sent
	while(true)
	{	
		std::cout << "Server Queue Length: " << this->getServerAlertQueue()->size() << '\n';
		std::cout << "Connections Length: " << this->getConnections()->size() << '\n';
		// Reads and executes server commands
		if(this->getServerAlertQueue()->size() > 0)
		{
			std::for_each(this->getConnections()->begin(), this->getConnections()->end(), [](auto connection)
			{
				connection.second->join();
				std::cout << "Loginworkerthread closed\n";
			});
			
			std::cout << "CMD: exit loginserver\n";
			break;
		}

		// Set up for new connection
		sockaddr_in client_addr;
		socklen_t clientSize = sizeof(client_addr);

		std::thread loginWorkerThread;
		std::shared_ptr<Client> client(new Client());

		struct pollfd *fds;
		int fdcount = this->getConnectionsLength() + 1;
		
		fds = (pollfd*)malloc(sizeof(struct pollfd) * fdcount);
		fds[0].fd = this->getSocket();
		fds[0].events = POLLIN;
		
		int j = 0;
		Connections* temp = this->getConnections();
		std::for_each(temp->begin(), temp->end(), [temp, &fds, &j](auto connection) 
		{
			fds[j + 1].fd = connection.first->getSocket();
			fds[j + 1].events = POLLIN;
			j++;
		});
	
		try
		{
			if(poll(fds, fdcount, this->POLL_TIMEOUT))
			{
				int sock = accept(this->getSocket(),
					         (sockaddr*) &client_addr, 
						 &clientSize);
				if(sock > -1)
				{
					client->setSocket(sock);
					client->setHint(client_addr);
					char str[INET_ADDRSTRLEN];
					inet_ntop(AF_INET, &(client->getHint()->sin_addr), str, INET_ADDRSTRLEN);
					std::cout << "Client connected" << '\n';
					std::cout << "Socket: " << client->getSocket() << '\n';
					std::cout << "Port: " << client->getHint()->sin_port << '\n';
					std::cout << "IP: " << str << '\n';
					try
					{
						this->spawnWorker(client); 
					}
					catch(const std::exception& ex)
					{
						std::cout << ex.what() << '\n';
					}
				}
			}
		}
		catch(const std::exception& ex)
		{
			std::cout << ex.what() << '\n';
		}
		free(fds);
	}
	this->disconnect();
	return true;
}

bool LoginServer::connect()
{
	return true;
}

bool LoginServer::disconnect()
{
	std::cout << "Login server shutting down" << '\n';
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
	std::shared_ptr<std::thread> loginWorkerThread = std::make_shared<std::thread>([this, client]() { 
		LoginWorker loginWorker = LoginWorker(this, client);
		loginWorker.run();
	});	
	this->addConnection(std::move(client), std::move(loginWorkerThread));
	
	
	
	//workers.get()->emplace(workers.get()->size(), std::make_shared<LoginWorker>(loginWorker));
	
	
	return true;
}


