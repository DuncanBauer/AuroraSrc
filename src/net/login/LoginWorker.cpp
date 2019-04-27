#include "LoginWorker.h"
#include "LoginServer.h"

#include <queue>

LoginWorker::LoginWorker()
{
}

LoginWorker::LoginWorker(LoginServer* loginServer, std::shared_ptr<Client> client)
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
	PacketStream ps;
	ps.setPacket(MaplePacketCreator::getHandshake());
	
//	std::cout << this->client.get()->getSocket() << '\n';

	send(this->client->getSocket(), ps.getByteStream().str().c_str(), ps.getPacket().length + 1, 0);
	std::cout << ps.getByteStream().str() << '\n';
	std::cout << ps.getByteStreamHex().str() << '\n';

	while(true)
	{
	//	std::unique_lock<std::mutex> lock(*(this->loginServer->getMutex()), std::defer_lock);
	//	lock.lock();
	//	std::cout << "Worker lock\n";
		if(this->loginServer->getServerAlertQueue()->size() > 0)
		{
			std::cout << "CMD: exit loginworker\n";
			break;
		}

	//	lock.unlock();

		byte buff[512];
		memset(buff, 0, 512);

		int bytesRecv = recv(client->getSocket(), buff, 512, 0);
		if(bytesRecv > 0)
		{
			std::cout << "# Bytes: " << bytesRecv << '\n';
			std::cout << "Data: " << buff << '\n';
		}
	}
	this->disconnect();
}

void LoginWorker::connect()
{
}

void LoginWorker::disconnect()
{
	std::cout << "Ending loginworker thread" << '\n';
	//this->loginServer->getConnections()[this->client]->join();
	//loginServer->removeConnection(client);
	//this->client.get()->disconnect();
	//this->client.reset();
}

void LoginWorker::reconnect()
{
}

void LoginWorker::stop()
{
}
