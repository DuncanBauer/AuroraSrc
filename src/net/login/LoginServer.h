#ifndef LOGINSERVER_H
#define LOGINSERVER_H

/*
 * Included from TCPServerSocket.h
 *
 * #include "TCPSocket.h"
 * #include <poll>
 * #include <vector>
 * #include <iterator>
 * #include <thread>
 *
 */

class TCPClientSocket;

#include "../../tools/packets/PacketStream.h"
#include "LoginWorker.h"
#include "../GenericMapleServer.h"

using LoginConnections = std::map<std::shared_ptr<TCPClientSocket>, std::shared_ptr<LoginWorker>>;

class LoginServer : public GenericMapleServer
{
	public:
		LoginServer(char* ip, int port, Master* master, int id);
		virtual ~LoginServer();
	
		virtual bool run();
		virtual bool connect();
		virtual bool disconnect();
		virtual bool reconnect();
		virtual bool alertServer(int command);
		virtual bool spawnWorker(std::shared_ptr<TCPClientSocket> client);
		
		void addConnection(std::shared_ptr<TCPClientSocket> client, std::shared_ptr<LoginWorker> worker);
		void removeConnection(std::shared_ptr<TCPClientSocket> client);
		LoginConnections* getConnections();
		int getConnectionsLength();

	private:
		std::unique_ptr<LoginConnections> connections;

};


#endif
