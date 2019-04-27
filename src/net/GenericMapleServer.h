#ifndef GENERICMAPLESERVER_H
#define GENERICMAPLESERVER_H

#include "sockets/TCPServerSocket.h"

#include <queue>

class Master;

using AlertQueue = std::priority_queue<int>;


class GenericMapleServer: public TCPServerSocket 
{
	public:
		GenericMapleServer(char* ip, int port, Master* master, int playerCount);
		virtual ~GenericMapleServer();
	
		Master* getMaster();	
		void setMaster(Master* master);

		AlertQueue* getServerAlertQueue();
		void setServerAlertQueue(AlertQueue* serverAlertQueue);
 
		virtual bool run();
		virtual bool connect();
		virtual bool disconnect();
		virtual bool reconnect();
		virtual bool alertServer(int command);
		virtual bool spawnWorker(std::shared_ptr<TCPClientSocket> client);
	
	private:
		Master* master;
		int playerCount;

	protected:
		AlertQueue* serverAlertQueue;
};

#endif
