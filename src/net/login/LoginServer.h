#ifndef LOGINSERVER_H
#define LOGINSERVER_H

/*
 * Included from TCPServerSocket.h
 *
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
#include "../sockets/TCPServerSocket.h"
#include "../sockets/TCPClientSocket.h"


#if defined(__linux__)
    #include <poll.h>
    #include "../sockets/TCPSocket.h"
#else
    #include "../sockets/TCPSocketWindows.h"
#endif

#include <iterator>
#include <mutex>
#include <algorithm>
#include <memory>
#include <iostream>
#include <cerrno>


template <class TCPSock>
class LoginServer : public GenericMapleServer<TCPSock>
{
    	using LoginConnections = std::map<std::shared_ptr<TCPClientSocket<TCPSock>>, std::shared_ptr<LoginWorker<TCPSock>>>;
	
	public:
        LoginServer(char* ip, int port, Master* master, int id) : GenericMapleServer<TCPSock>(ip, port, master, id)
        {
        	std::map<std::string, std::string> config = ConfigParser::getValuesFromFile("login.conf");
        	this->POLL_TIMEOUT = std::stoi(config["loginserver.poll.timeout"]);
        	this->connections.reset(new LoginConnections());
         	//this->conn = new MySQLConn();
        }

        ~LoginServer()
        {
		this->connections.reset();
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

        bool listening()
        {
            #ifdef LINUX
                std::cout << "Listening on Linux: " << '\n';
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
		    std::cout << "LOGINSERVER: LISTENING (J)" << j << '\n';
                });
                this->getMutex()->unlock();
		temp = nullptr;

                // Poll for incoming connections enter if activity on one of the fds
                if(poll(fds, fdcount, this->POLL_TIMEOUT))
                {
		    std::cout << "LOGINSERVER: LISTENING (CLIENT CONNECTING)" << '\n';
                    // Loop for number of current connections + 1 ( for the server socket )
                    for(int k = 0; k < fdcount; ++k)
                    {
			// If the socket is closed, skip
 			//if(fds[k].revents == 0)
			//{
			//continue;
			//}
			// If there's no data to read, something fucky happened?
			//if(fds[k].revents != POLLIN)
			//{
			//break;
			//}

                        // If the fd is the server socket, accept incoming connection
                        if(fds[k].fd == this->getSocket())
                        {
                            char host[NI_MAXHOST];
                            char svc[NI_MAXSERV];
			    int sock;
			    // Accept all incoming connections
			    do
			    {
                            sock = accept(this->getSocket(),
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

                                std::shared_ptr<TCPClientSocket<TCPSock>> client(new TCPClientSocket<TCPSock>());
                                client->setSocket(sock);
                                client->setHint(client_addr);
				std::cout << "LOGINSERVER: LISTENING (1 CLIENT SOCKET = " << client->getSocket() << ")" << '\n';
                                this->spawnWorker(client);
				std::cout << "LOGINSERVER: LISTENING (2 CLIENT SOCKET = " << client->getSocket() << ")" << '\n';
                            }
			    else
			    {
			    	if(errno != EWOULDBLOCK)
				{
					std::cout << "LOGINSERVER: LISTENING (SOMETHING FUCKY HAPPENED HERE)" << '\n';
				}
				else
				{
					std::cout << "LOGINSERVER: LISTENING (NO PENDING CONNECTIONS)" << '\n';
				}
			    }
			    } while(sock != -1);
                        }
			else
			{
				std::cout << "LOGINSERVER: LISTENING (THERES INCOMING DATA TO READ FROM A VALID CONNECTION)" << '\n';
			}
                    }
                }
                free(fds);
            #else
                std::cout << "Listening on Windows: " << '\n';
                int iResult;
                int iSendResult;
                SOCKET ClientSocket = INVALID_SOCKET;
                SOCKET ListenSocket = this->getSocket();
                const int DEFAULT_BUFLEN = 512;
                char recvbuf[DEFAULT_BUFLEN];
                int recvbuflen = DEFAULT_BUFLEN;

                iResult = listen(ListenSocket, SOMAXCONN);
                if (iResult == SOCKET_ERROR) {
                    printf("listen failed with error: %d\n", WSAGetLastError());
                    closesocket(ListenSocket);
                    WSACleanup();
                    return 1;
                }

                // Accept a client socket
                ClientSocket = accept(ListenSocket, NULL, NULL);
                if (ClientSocket == INVALID_SOCKET) {
                    printf("accept failed with error: %d\n", WSAGetLastError());
                    closesocket(ListenSocket);
                    WSACleanup();
                    return 1;
                }

                // Receive until the peer shuts down the connection
                do {

                    iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
                    if (iResult > 0) {
                        printf("Bytes received: %d\n", iResult);

                    // Echo the buffer back to the sender
                        iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
                        if (iSendResult == SOCKET_ERROR) {
                            printf("send failed with error: %d\n", WSAGetLastError());
                            closesocket(ClientSocket);
                            WSACleanup();
                            return 1;
                        }
                        printf("Bytes sent: %d\n", iSendResult);
                    }
                    else if (iResult == 0)
                        printf("Connection closing...\n");
                    else  {
                        printf("recv failed with error: %d\n", WSAGetLastError());
                        closesocket(ClientSocket);
                        WSACleanup();
                        return 1;
                    }

                } while (iResult > 0);

                // shutdown the connection since we're done
                iResult = shutdown(ClientSocket, SD_SEND);
                if (iResult == SOCKET_ERROR) {
                    printf("shutdown failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }

                // cleanup
                closesocket(ClientSocket);


                return true;
            #endif
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
		std::cout << "LOGINSERVER: SPAWNWORKER\n";
        	// Create LoginWorker for client
        	std::shared_ptr<LoginWorker<TCPSock>> loginWorker(new LoginWorker<TCPSock>(this, client));

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

    
        void addConnection(std::shared_ptr<TCPClientSocket<TCPSock>> client, std::shared_ptr<LoginWorker<TCPSock>> worker)
        {
        	this->getMutex()->lock();
        	this->connections->emplace(client, worker);
        	this->getMutex()->unlock();
        }
/*
        void removeConnection(std::shared_ptr<TCPClientSocket> client)
        {
        	this->getMutex()->lock();
        	this->connections->erase(client);
        	this->getMutex()->unlock();
        }
*/
        LoginConnections* getConnections()
        {
        	return this->connections.get();
        }

        int getConnectionsLength()
       	{
        	return this->connections->size();
        }
    
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
