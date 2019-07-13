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

//class TCPClientSocket;

//#include "../db/MySQLConn.h"
#include "../../tools/PacketStream.h"
#include "LoginWorker.h"
#include "../GenericMapleServer.h"
#include "../../Master.h"
#include "../../tools/ConfigParser.h"

#if defined(__linux__)
    #include <poll.h>
    #include "../sockets/TCPSocket.h"
#else
    #include "../sockets/TCPSocketWindows.h"
#endif
#include "../sockets/TCPServerSocket.h"
#include <iterator>
#include <mutex>
#include <algorithm>
#include <memory>
#include <iostream>
#include <cerrno>


//class LoginWorker<TCPSocketWindows>;
//class LoginWorker<TCPSocket>;

template <class TCPSock>
class LoginServer : public GenericMapleServer<TCPSock>
{

    using LoginConnections = std::map<std::shared_ptr<TCPClientSocket<TCPSock>>, std::shared_ptr<LoginWorker<TCPSock>>>;
	public:
        LoginServer(char* ip, int port, Master* master, int id) : GenericMapleServer<TCPSock>(ip, port, master, id)
        {
        	std::map<std::string, std::string> config = ConfigParser::getValuesFromFile("login.conf");
        	this->POLL_TIMEOUT = std::stoi(config["loginserver.poll.timeout"]);
        	//this->connections.reset(new LoginConnections());
         	//this->conn = new MySQLConn();
        }

        ~LoginServer()
        {
        /*	if(this->conn != nullptr)
        	{
        		delete conn;
        	}
        */
        }

        bool run()
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
                this->listening();
        	}

            #ifndef LINUX
                WSACleanup();
            #endif
        	this->disconnect();
        	return true;
        }

        bool connect()
        {
        	return true;
        }

        bool disconnect()
        {
        	std::cout << "LOGINSERVER SHUTTING DOWN\n" << '\n';
        	this->setStatus(OFFLINE);
        	return true;
        }

        bool reconnect()
        {
        	return true;
        }

        bool alertServer(int command)
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

        bool spawnWorker(std::shared_ptr<TCPClientSocket<TCPSock>> client)
        {
        	// Create LoginWorker for client
        	std::shared_ptr<LoginWorker<TCPSock>> loginWorker(new LoginWorker<TCPSock>(this, client));

        	// Run LoginWorker on separate thread and detach it ( loginserver waits while it cleans itself )
        	std::shared_ptr<std::thread> loginWorkerThread = std::make_shared<std::thread>([loginWorker]()
        	{
        		loginWorker->run();
        	});
        	loginWorkerThread->detach();

        	// Add client/worker pair as connection
        	//this->addConnection(client, loginWorker);

        	return true;
        }

    /*
        void addConnection(std::shared_ptr<TCPClientSocket> client, std::shared_ptr<LoginWorker> worker)
        {
        	this->getMutex()->lock();
        	this->connections->emplace(client, worker);
        	this->getMutex()->unlock();
        }

        void removeConnection(std::shared_ptr<TCPClientSocket> client)
        {
        	this->getMutex()->lock();
        	this->connections->erase(client);
        	this->getMutex()->unlock();
        }

        LoginConnections* getConnections()
        {
        	return this->connections.get();
        }

        int getConnectionsLength()
        {
        	return this->connections->size();
        }
    */
        /*
		LoginServer(char* ip, int port, Master* master, int id);
		~LoginServer();

		bool run();
		bool connect();
		bool disconnect();
		bool reconnect();
		bool alertServer(int command);
		bool spawnWorker(std::shared_ptr<TCPClientSocket> client);

		void addConnection(std::shared_ptr<TCPClientSocket> client, std::shared_ptr<LoginWorker> worker);
		void removeConnection(std::shared_ptr<TCPClientSocket> client);
		LoginConnections* getConnections();
		int getConnectionsLength();
*/
	private:
        int POLL_TIMEOUT;
	//	MySQLConn* conn;
		std::unique_ptr<LoginConnections> connections;

};


#endif
