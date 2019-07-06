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

LoginServer::LoginServer(char* ip, int port, Master* master, int id) : GenericMapleServer(ip, port, master, id)
{
	std::map<std::string, std::string> config = ConfigParser::getValuesFromFile("login.conf");
	this->POLL_TIMEOUT = std::stoi(config["loginserver.poll.timeout"]);
	this->connections.reset(new LoginConnections());
}

LoginServer::~LoginServer()
{
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

		// Set up for new connection
		sockaddr_in client_addr;
		socklen_t clientSize = sizeof(client_addr);

		// Initialize pollfd structure
		struct pollfd *fds;
		int fdcount = this->getConnectionsLength() + 1;
		fds = (pollfd*)malloc(sizeof(struct pollfd) * fdcount);
		fds[0].fd = this->getSocket();
		fds[0].events = POLLIN;

		// Lock and add current connections to pollfd struct
		int j = 0;
		LoginConnections* temp = this->getConnections();
		this->getMutex()->lock();
		std::for_each(temp->begin(), temp->end(), [temp, &fds, &j](auto connection)
		{
			fds[j + 1].fd = connection.first->getSocket();
			fds[j + 1].events = POLLIN;
			j++;
		});
		this->getMutex()->unlock();

		// Poll for incoming connections enter if activity on one of the fds
		if(poll(fds, fdcount, this->POLL_TIMEOUT))
		{
			// Loop for number of current connections + 1 ( for the server socket )
			for(int k = 0; k < fdcount; ++k)
			{
				// If the fd is the server socket, accept incoming connection
				if(fds[k].fd == this->getSocket())
				{
					char host[NI_MAXHOST];
					char svc[NI_MAXSERV];
					int sock = accept(this->getSocket(),
							  (sockaddr*) &client_addr,
							  &clientSize);

					// If the connection is accepted, spawn their session on a LoginWorker
					if(sock > -1)
					{
						memset(host, 0, NI_MAXHOST);
						memset(svc, 0, NI_MAXSERV);
						int result = getnameinfo((sockaddr*)&client_addr,
									 sizeof(client_addr),
									 host,
									 NI_MAXHOST,
									 svc,
									 NI_MAXSERV,
									 0);
						if(result)
						{
							std::cout << host << " connected on " << svc << '\n';
						}
						else
						{
							inet_ntop(AF_INET, &client_addr.sin_addr, host, NI_MAXHOST);
							std::cout << host << " connected on " << ntohs(client_addr.sin_port) << '\n';
						}

						std::shared_ptr<TCPClientSocket> client(new TCPClientSocket());
						client->setSocket(sock);
						client->setHint(client_addr);
						this->spawnWorker(client);

					}
				}
			}
		}
		free(fds);
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
