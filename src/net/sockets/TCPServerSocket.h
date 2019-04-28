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

enum ServerStatus
{
	OFFLINE,
	INITIALIZING,
	ONLINE
};


class TCPServerSocket: public TCPSocket 
{
	public:
		int POLL_TIMEOUT = 500;

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
	
	private:
		ServerStatus status;
		std::mutex mtx;
		int id;
};

#endif
