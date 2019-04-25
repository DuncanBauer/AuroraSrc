#ifndef CHANNELSERVER_H
#define CHANNELSERVER_H

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
#include "ChannelWorker.h"
#include "../GenericMapleServer.h"


class ChannelServer : public GenericMapleServer
{
	public:
		ChannelServer(char* ip, int port, Master* master, int id);
		virtual ~ChannelServer();
		
		virtual bool run();
		virtual bool connect();
		virtual bool disconnect();
		virtual bool reconnect();
		virtual bool alertServer(int command);
		virtual bool spawnWorker(std::shared_ptr<Client> client);

	private:
};


#endif
