#ifndef CHANNELWORKER_H
#define CHANNELWORKER_H


#include "../../tools/packets/MaplePacketCreator.h"
#include "../sockets/TCPClientSocket.h"
#include "../GenericWorker.h"

#include <iostream>

class ChannelServer;

class ChannelWorker : public GenericWorker
{
	public:
		ChannelWorker();
		ChannelWorker(std::shared_ptr<ChannelServer> channelServer, std::shared_ptr<TCPClientSocket> client);
		virtual ~ChannelWorker();
		
		virtual void initialize();
		virtual void run();
		virtual void connect();
		virtual void disconnect();
		virtual void reconnect();
		virtual void stop();

	private:
		std::shared_ptr<ChannelServer> channelServer;
		std::shared_ptr<TCPClientSocket> client;
};

#endif
