#ifndef TCPSERVERSOCKET_H
#define TCPSERVERSOCKET_H

#include "TCPSocket.h"

#include <map>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>
#include <exception>

class TCPClientSocket;

using Connections = std::map<std::shared_ptr<TCPClientSocket>, std::shared_ptr<std::thread>>;

enum ServerStatus
{
	OFFLINE,
	INITIALIZING,
	ONLINE
};


class TCPServerSocket: public TCPSocket 
{
	public:
		const int POLL_TIMEOUT = 500;

		TCPServerSocket(char* ip, int port, int id);
		virtual ~TCPServerSocket();
		
		bool initialize(char* ip, int port);
		virtual bool run();	
		virtual bool connect();
		virtual bool disconnect();
		virtual bool reconnect();
		virtual bool alertServer(int command);
		virtual bool spawnWorker(std::shared_ptr<TCPClientSocket> client);
	
		int getID();
		void setID(int id);
		
		ServerStatus getStatus();
		void setStatus(ServerStatus status);
	
		std::mutex* getMutex();
	
		int getConnectionsLength();
		Connections* getConnections();
		void addConnection(std::shared_ptr<TCPClientSocket> client, std::shared_ptr<std::thread> thread);
		void removeConnection(std::shared_ptr<TCPClientSocket> client);

	private:
		std::unique_ptr<Connections> connections;
		ServerStatus status;
		std::mutex mtx;
		int id;
};

#endif
