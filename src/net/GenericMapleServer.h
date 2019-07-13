#ifndef GENERICMAPLESERVER_H
#define GENERICMAPLESERVER_H

/*
#if defined(__linux__)
    #include "sockets/TCPServerSocket.h"
#else
    //#include "sockets/TCPServerSocketWindows.h"
    #include "sockets/TCPServerSocket.h"
#endif
*/
#include "../Master.h"
#include "sockets/TCPClientSocket.h"
#include "sockets/TCPServerSocket.h"

#include <iostream>
#include <queue>

//class Master;

using AlertQueue = std::priority_queue<int>;

template <class TCPSock>
class GenericMapleServer: public TCPServerSocket<TCPSock>
{
	public:
        GenericMapleServer(char* ip, int port, Master* master, int id) : TCPServerSocket<TCPSock>(ip, port, id)
        {
        //	std::cout << "GenericMapleServer constructor called" << '\n';
        	this->setMaster(master);
        	this->setServerAlertQueue(master->getServerAlertQueue());
        	this->playerCount = 0;
        }

        ~GenericMapleServer()
        {
        //	std::cout << "GenericMapleServer destructor called" << '\n';
        	this->master = NULL;
        	this->serverAlertQueue = NULL;
        	this->playerCount = 0;
        }

        Master* getMaster()
        {
        	return master;
        }

        void setMaster(Master* master)
        {
        	this->master = master;
        }

        AlertQueue* getServerAlertQueue()
        {
        	return serverAlertQueue;
        }

        void setServerAlertQueue(AlertQueue* alertQueue)
        {
        	this->serverAlertQueue = alertQueue;
        }

        /*
		GenericMapleServer(char* ip, int port, Master* master, int id);
		~GenericMapleServer();

		Master* getMaster();
		void setMaster(Master* master);

		AlertQueue* getServerAlertQueue();
		void setServerAlertQueue(AlertQueue* serverAlertQueue);
/*
		bool run();
		bool connect();
		bool disconnect();
		bool reconnect();
		bool alertServer(int command);
		bool spawnWorker(std::shared_ptr<TCPClientSocket<TCPSock>> client);
*/
	private:
		Master* master;
		int playerCount;

	protected:
		AlertQueue* serverAlertQueue;
};

#endif
