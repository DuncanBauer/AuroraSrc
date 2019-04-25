#include "ChannelServer.h"
#include "../../client/Client.h"
#include "../../Master.h"

#include <iterator>
#include <poll.h>
#include <mutex>
#include <algorithm>
#include <memory>
#include <iostream>


ChannelServer::ChannelServer(char* ip, int port, Master* master, int id) : GenericMapleServer(ip, port, master, id)
{
}

ChannelServer::~ChannelServer()
{
}

bool ChannelServer::run()
{	/*
	this->setStatus(1);

	while(true)
	{	
		std::unique_lock<std::mutex> lock(this->getMaster()->mutex, std::defer_lock);
		lock.lock();
		if(this->getMaster()->serverAlertQueue.size() > 0)
		{
			std::cout << "Shutting down channel server " << this->getID() << '\n';
			break;
		}
		lock.unlock();


		sockaddr_in client_addr;
		socklen_t clientSize = sizeof(client_addr);

		Client* client = new Client();

		struct pollfd *fds;
		int fdcount = this->getConnectionsLength() + 1;
		fds = (pollfd*)malloc(sizeof(struct pollfd) * fdcount);

		fds[0].fd = this->getSocket();
		fds[0].events = POLLOUT | POLLIN;

		int j = 0;
		std::map<std::thread*, Client*>* temp = this->getConnections();
		std::for_each(temp->begin(), temp->end(), [&temp, &fds, &j](auto connection)
		{
			fds[j + 1].fd = temp->at(connection.first)->getSocket();
			fds[j + 1].events = POLLOUT | POLLIN;
		});

		if(poll(fds, fdcount, this->POLL_TIMEOUT))
		{
			client->setSocket(accept(this->getSocket(),
					          (sockaddr*) &client_addr, 
						  &clientSize));
		}

		if(client->getSocket() != -1 && client->getSocket() != 0)
		{
			// Spawn client_addr on new thread
		//	std::cout << "Client connected" << '\n';
		
			std::thread channelWorkerThread = std::thread([=] { 
				this->spawnWorker(client); 
			});
			channelWorkerThread.detach();
			
			this->addConnection(&channelWorkerThread, client);
		}
		else
		{
			delete client;
		}
		free(fds);
	}

	std::for_each(this->getConnections()->begin(), this->getConnections()->end(), [](auto connection)
	{
		connection.first->join();
	});
	*/
	return true;
}

bool ChannelServer::connect()
{
	return true;
}

bool ChannelServer::disconnect()
{
	return true;
}

bool ChannelServer::reconnect()
{
	return true;
}

bool ChannelServer::alertServer(int command)
{
	return true;
}

bool ChannelServer::spawnWorker(std::shared_ptr<Client> client)
{
	ChannelWorker channelWorker = ChannelWorker(std::shared_ptr<ChannelServer>(this), client);
	channelWorker.run();
	return true;
}


