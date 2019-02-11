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


class LoginServer : public GenericMapleServer
{
	public:
		LoginServer(char* ip, int port, std::shared_ptr<Master> master, int id);
		virtual ~LoginServer();
	
		virtual bool run();
		virtual bool connect();
		virtual bool disconnect();
		virtual bool reconnect();
		virtual bool alertServer(int command);
		virtual bool spawnWorker(std::shared_ptr<Client> client);

	private:
};


#endif
