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

#include "../../tools/packets/PacketStream.h"
#include "LoginWorker.h"
#include "../GenericMapleServer.h"

//using Workers = std::map<int, std::shared_ptr<LoginWorker>>;

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

	private:
//		std::unique_ptr<Workers> workers;
};


#endif
