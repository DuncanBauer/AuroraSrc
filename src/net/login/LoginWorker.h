#ifndef LOGINWORKER_H
#define LOGINWORKER_H


#include "../../tools/MaplePacketCreator.h"
#include "../sockets/TCPClientSocket.h"
#include "../GenericWorker.h"

#include <iostream>

class LoginServer;

class LoginWorker : public GenericWorker
{
	public:
		LoginWorker();
		LoginWorker(LoginServer* loginServer, std::shared_ptr<TCPClientSocket> client);
		virtual ~LoginWorker();

		virtual void initialize();
		virtual void run();
		virtual void connect();
		virtual void disconnect();
		virtual void reconnect();
		virtual void stop();

	private:
		LoginServer* loginServer;
		std::shared_ptr<TCPClientSocket> client;
};

#endif
