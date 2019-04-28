#include "LoginWorker.h"
#include "LoginServer.h"

#include <queue>

LoginWorker::LoginWorker()
{
}

LoginWorker::LoginWorker(LoginServer* loginServer, std::shared_ptr<TCPClientSocket> client)
{
	this->loginServer = loginServer;
	this->client = client;
}

LoginWorker::~LoginWorker()
{
	this->client.reset();
	this->loginServer = NULL;
}

void LoginWorker::initialize()
{
}

void LoginWorker::run()
{
	// Create and send handshake to launch client
	PacketStream ps;
	ps.setPacket(MaplePacketCreator::getHandshake());

	byte* arr;
	arr = (byte*)malloc(sizeof(byte) * ps.getPacket().length + 1);
	ps.nullTermBytes(arr);

	send(this->client->getSocket(), arr, ps.getPacket().length+1, 0);
	free(arr);

	// Listen for packets until we can't?
	while(true)
	{
		if(this->loginServer->getServerAlertQueue()->size() > 0)
		{
			std::cout << "CMD: exit loginworker\n";
			break;
		}

		byte buff[512];
		memset(buff, 0, 512);

		int bytesRecv = recv(client->getSocket(), buff, 512, 0);
		if(bytesRecv > 0)
		{
			std::cout << "# Bytes: " << bytesRecv << '\n';
			std::cout << "Data: " << buff << '\n';
		}
		else if(bytesRecv == 0)
		{
			break;
		}
	}
	this->disconnect();
}

void LoginWorker::connect()
{
}

void LoginWorker::disconnect()
{
	this->loginServer->removeConnection(this->client);
	this->client.reset();
}

void LoginWorker::reconnect()
{
}

void LoginWorker::stop()
{
}
