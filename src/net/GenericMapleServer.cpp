#include "GenericMapleServer.h"
#include "../Master.h"
#include "sockets/TCPClientSocket.h"

#include <iostream>


GenericMapleServer::GenericMapleServer(char* ip, int port, Master* master, int id) : TCPServerSocket(ip, port, id)
{
//	std::cout << "GenericMapleServer constructor called" << '\n';
	this->setMaster(master);
	this->setServerAlertQueue(master->getServerAlertQueue());
	this->playerCount = 0;
}

GenericMapleServer::~GenericMapleServer()
{
//	std::cout << "GenericMapleServer destructor called" << '\n';
	this->master = NULL;
	this->serverAlertQueue = NULL;
	this->playerCount = 0;
}

Master* GenericMapleServer::getMaster()
{
	return master;
}

void GenericMapleServer::setMaster(Master* master)
{
	this->master = master;
}

AlertQueue* GenericMapleServer::getServerAlertQueue()
{
	return serverAlertQueue;
}

void GenericMapleServer::setServerAlertQueue(AlertQueue* alertQueue)
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

bool GenericMapleServer::spawnWorker(std::shared_ptr<TCPClientSocket> client)
{
	return true;
}
