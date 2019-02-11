#ifndef GENERICMAPLESERVER_H
#define GENERICMAPLESERVER_H

#include "sockets/TCPServerSocket.h"

#include <queue>

class Master;

using AlertQueue = std::priority_queue<int>;


class GenericMapleServer: public TCPServerSocket 
{
	public:
		GenericMapleServer(char* ip, int port, std::shared_ptr<Master> master, int playerCount);
		virtual ~GenericMapleServer();
	
		std::shared_ptr<Master> getMaster();	
		void setMaster(std::shared_ptr<Master> master);

		std::weak_ptr<AlertQueue> getServerAlertQueue();
		void setServerAlertQueue(std::shared_ptr<AlertQueue> serverAlertQueue);
 
		virtual bool run();
		virtual bool connect();
		virtual bool disconnect();
		virtual bool reconnect();
		virtual bool alertServer(int command);
		virtual bool spawnWorker(std::shared_ptr<Client> client);
	
	private:
		std::shared_ptr<Master> master;
		std::weak_ptr<AlertQueue> serverAlertQueue;
		int playerCount;
};

#endif
