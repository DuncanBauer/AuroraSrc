#include "LoginServer.h"
#include "../../Master.h"
#include "../../tools/ConfigParser.h"

//#include <netdb.h>
//#include <sys/socket.h>
//#include <sys/types.h>
#include <iterator>
#include <mutex>
#include <poll.h>
#include <algorithm>
#include <memory>
#include <iostream>
#include <cerrno>
/*
LoginServer::LoginServer(char* ip, int port, Master* master, int id) : GenericMapleServer(ip, port, master, id)
{
	std::map<std::string, std::string> config = ConfigParser::getValuesFromFile("login.conf");
	this->POLL_TIMEOUT = std::stoi(config["loginserver.poll.timeout"]);
	//this->connections.reset(new LoginConnections());
 	//this->conn = new MySQLConn();
}

LoginServer::~LoginServer()
{
/*	if(this->conn != nullptr)
	{
		delete conn;
	}
}

bool LoginServer::run()
{
	this->setStatus(ONLINE);
	// Run until shutdown command is sent
	while(true)
	{
		// Reads and executes server commands
		if(this->getServerAlertQueue()->size() > 0)
		{
			std::cout << "WAITING FOR CONNECTIONS TO TERMINATE\n";
			while(true)
			{
				if(this->connections->size() == 0)
				{
					break;
				}
			}
			break;
		}

        this->listen();
	}
	this->disconnect();
	return true;
}

bool LoginServer::connect()
{
	return true;
}

bool LoginServer::disconnect()
{
	std::cout << "LOGINSERVER SHUTTING DOWN\n" << '\n';
	this->setStatus(OFFLINE);
	return true;
}

bool LoginServer::reconnect()
{
	return true;
}

bool LoginServer::alertServer(int command)
{
	std::lock_guard<std::mutex> lock(*(this->getMutex()));
	try
	{
		this->serverAlertQueue->push(command);
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception caught alerting server" << '\n';
	}
	return true;
}

bool LoginServer::spawnWorker(std::shared_ptr<TCPClientSocket> client)
{
	// Create LoginWorker for client
	std::shared_ptr<LoginWorker> loginWorker(new LoginWorker(this, client));

	// Run LoginWorker on separate thread and detach it ( loginserver waits while it cleans itself )
	std::shared_ptr<std::thread> loginWorkerThread = std::make_shared<std::thread>([loginWorker]()
	{
		loginWorker->run();
	});
	loginWorkerThread->detach();

	// Add client/worker pair as connection
	this->addConnection(client, loginWorker);

	return true;
}

void LoginServer::addConnection(std::shared_ptr<TCPClientSocket> client, std::shared_ptr<LoginWorker> worker)
{
	this->getMutex()->lock();
	this->connections->emplace(client, worker);
	this->getMutex()->unlock();
}

void LoginServer::removeConnection(std::shared_ptr<TCPClientSocket> client)
{
	this->getMutex()->lock();
	this->connections->erase(client);
	this->getMutex()->unlock();
}

LoginConnections* LoginServer::getConnections()
{
	return this->connections.get();
}

int LoginServer::getConnectionsLength()
{
	return this->connections->size();
}
*/
