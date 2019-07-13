#include "GenericMapleServer.h"
#include "../Master.h"
#include "sockets/TCPClientSocket.h"

#include <iostream>
/*
template <class TCPServer, class TCPSock>
GenericMapleServer<TCPServer, TCPSock>::GenericMapleServer(char* ip, int port, Master* master, int id) : TCPServer(ip, port, id)
{
//	std::cout << "GenericMapleServer constructor called" << '\n';
	this->setMaster(master);
	this->seTCPServerAlertQueue(master->getServerAlertQueue());
	this->playerCount = 0;
}

template <class TCPServer, class TCPSock>
GenericMapleServer<TCPServer, TCPSock>::~GenericMapleServer()
{
//	std::cout << "GenericMapleServer destructor called" << '\n';
	this->master = NULL;
	this->serverAlertQueue = NULL;
	this->playerCount = 0;
}

template <class TCPServer, class TCPSock>
Master* GenericMapleServer<TCPServer, TCPSock>::getMaster()
{
	return master;
}

template <class TCPServer, class TCPSock>
void GenericMapleServer<TCPServer, TCPSock>::setMaster(Master* master)
{
	this->master = master;
}

template <class TCPServer, class TCPSock>
AlertQueue* GenericMapleServer<TCPServer, TCPSock>::getServerAlertQueue()
{
	return serverAlertQueue;
}

template <class TCPServer, class TCPSock>
void GenericMapleServer<TCPServer, TCPSock>::setServerAlertQueue(AlertQueue* alertQueue)
{
	this->serverAlertQueue = alertQueue;
}

/*
template <class TCPServer, class TCPSock>
bool GenericMapleServer<TCPServer, TCPSock>::run()
{
	return true;
}

template <class TCPServer, class TCPSock>
bool GenericMapleServer<TCPServer, TCPSock>::connect()
{
	return true;
}

template <class TCPServer, class TCPSock>
bool GenericMapleServer<TCPServer, TCPSock>::disconnect()
{
	return true;
}

template <class TCPServer, class TCPSock>
bool GenericMapleServer<TCPServer, TCPSock>::reconnect()
{
	return true;
}

template <class TCPServer, class TCPSock>
bool GenericMapleServer<TCPServer, TCPSock>::alertServer(int command)
{
	return true;
}

template <class TCPServer, class TCPSock>
bool GenericMapleServer<TCPServer, TCPSock>::spawnWorker(std::shared_ptr<TCPClientSocket<TCPSock>> client)
{
	return true;
}
*/
