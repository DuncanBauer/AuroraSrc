#include "GenericMapleServer.h"
#include "../Master.h"
#include "../client/Client.h"

#include <iostream>


GenericMapleServer::GenericMapleServer(char* ip, int port, std::shared_ptr<Master> master, int id) : TCPServerSocket(ip, port, id)
{
	std::cout << "GenericMapleServer constructor called" << '\n';
	this->setMaster(master);
	this->setServerAlertQueue(this->getMaster()->getServerAlertQueue());
	this->playerCount = 0;
}

GenericMapleServer::~GenericMapleServer()
{
	std::cout << "GenericMapleServer destructor called" << '\n';
	this->master.reset();
	this->serverAlertQueue.reset();
	this->playerCount = 0;
}

std::shared_ptr<Master> GenericMapleServer::getMaster()
{
	return master;
}

void GenericMapleServer::setMaster(std::shared_ptr<Master> master)
{
	this->master = master;
}

std::weak_ptr<AlertQueue> GenericMapleServer::getServerAlertQueue()
{
	return this->serverAlertQueue;
}

void GenericMapleServer::setServerAlertQueue(std::shared_ptr<AlertQueue> alertQueue)
{
	this->serverAlertQueue = alertQueue;
}

bool GenericMapleServer::run()
{
	return true;
}


bool GenericMapleServer::connect()
{
	return true;
}

bool GenericMapleServer::disconnect()
{
	return true;
}


bool GenericMapleServer::reconnect()
{
	return true;
}

bool GenericMapleServer::alertServer(int command)
{
	return true;
}

bool GenericMapleServer::spawnWorker(std::shared_ptr<Client> client)
{
	return true;
}
