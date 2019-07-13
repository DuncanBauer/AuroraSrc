#ifndef TCPSERVERSOCKET_H
#define TCPSERVERSOCKET_H

#if defined(__linux__)
    #define LINUX
    #include <poll.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <sys/time.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <memory>
    #include "TCPSocket.h"
#else
    #include <winsock2.h>
    #include <memory>
    #include <ws2tcpip.h>
    #include <cstdlib>
    #include <string>
    #include <cstring>
    #include <iostream>
    #include <windows.h>
    #include <stdio.h>
    #include "TCPSocketWindows.h"
#endif

#include "TCPClientSocket.h"

#include <iterator>
#include <algorithm>
#include <memory>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>
#include <exception>
#include <cstdio>


enum ServerStatus
{
	OFFLINE,
	INITIALIZING,
	READY,
	ONLINE
};

template <class TCPSock>
class TCPServerSocket: public TCPSock
{
	public:
        TCPServerSocket(char* ip, int port, int id)
        {
        	this->setStatus(OFFLINE);
        	if(this->initialize(ip, port))
        	{
        		this->setStatus(READY);
        	}
        	this->setID(id);
        }

        ~TCPServerSocket()
        {
        }

        bool initialize(char* address, int port)
        {
            this->ip = address;
            this->port = port;
        	std::cout << "INITIALIZING SERVER\n";
        	this->setStatus(INITIALIZING);


            #ifdef LINUX
                std::cout << "Initializing on Linux: " << '\n';
                this->setSocket(socket(AF_INET, SOCK_STREAM, 0));
            	if(this->getSocket() < 0)
            	{
            		std::cerr << "Can\'t create socket\n";
            		return false;
            	}

            	this->getHint()->sin_family = AF_INET;
            	this->getHint()->sin_port = htons(port);
            	inet_pton(AF_INET, address, &(this->getHint()->sin_addr));

            	int on = 1;
            	if(setsockopt(this->getSocket(), SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
            	{
            		std::cerr << "Couldn't set socket reusable\n";
            		this->setStatus(OFFLINE);
            		return false;
            	}

            	if(ioctl(this->getSocket(), FIONBIO, (char *)&on) < 0)
            	{
            		std::cerr << "Couldn't set socket nonblocking\n";
            		this->setStatus(OFFLINE);
            		return false;
            	}

            	if(bind(this->getSocket(), (sockaddr*)(this->getHint()), sizeof(*this->getHint())) < 0)
            	{
            		std::cerr << "Couldn\'t bind socket to IP/PORT\n";
            		this->setStatus(OFFLINE);
            		return false;
            	}

            	if(listen(this->getSocket(), SOMAXCONN) < 0)
            	{
            		std::cerr << "Can\'t listen\n";
            		this->setStatus(OFFLINE);
            		return false;
            	}

            	return true;
            #else
                std::cout << "Initializing on Windows: " << '\n';
                int DEFAULT_BUFLEN = 512;

                WSADATA wsaData;
                int iResult;

                SOCKET ListenSocket = INVALID_SOCKET;

                struct addrinfo *result = NULL;
                struct addrinfo hints;

                int iSendResult;
                char recvbuf[DEFAULT_BUFLEN];
                int recvbuflen = DEFAULT_BUFLEN;

                // Initialize Winsock
                iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
                if (iResult != 0)
                {
                    printf("WSAStartup failed with error: %d\n", iResult);
                    return 1;
                }

                ZeroMemory(&hints, sizeof(hints));
                hints.ai_family = AF_INET;
                hints.ai_socktype = SOCK_STREAM;
                hints.ai_protocol = IPPROTO_TCP;
                hints.ai_flags = AI_PASSIVE;

                // Resolve the server address and port
                char buffer[5];
                sprintf(buffer, "%d", this->port);
                iResult = getaddrinfo(this->ip, buffer, &hints, &result);
                if ( iResult != 0 )
                {
                    printf("getaddrinfo failed with error: %d\n", iResult);
                    WSACleanup();
                    return 1;
                }

                // Create a SOCKET for connecting to server
                ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
                if (ListenSocket == INVALID_SOCKET)
                {
                    printf("socket failed with error: %ld\n", WSAGetLastError());
                    freeaddrinfo(result);
                    WSACleanup();
                    return 1;
                }

                // Setup the TCP listening socket
                iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
                if (iResult == SOCKET_ERROR)
                {
                    printf("bind failed with error: %d\n", WSAGetLastError());
                    freeaddrinfo(result);
                    closesocket(ListenSocket);
                    WSACleanup();
                    return 1;
                }
                this->setSocket(ListenSocket);
                this->setHint(hints);

                freeaddrinfo(result);
                return true;
            #endif
        }

        bool run()
        {
        /*  THIS IS HERE FOR REFERENCE
        	while(true)
        	{
        		sockaddr_in client;
        		socklen_t clientSize = sizeof(client);
        	//	char host[NI_MAXHOST];
        	//	char service[NI_MAXSERV];

        		TCPSocket* clientSock = new TCPSocket();

        		struct pollfd *fds;
        		int fdcount = this->getConnectionsLength() + 1;
        		fds = (pollfd*)malloc(sizeof(struct pollfd) * fdcount);
        		fds[0].fd = this->getSocket();
        		fds[0].events |= POLLOUT;

        		for(int i = 0; i < this->getConnectionsLength(); ++i)
        		{
        			fds[i + 1].fd = this->getConnections()[i]->getSocket();
        			fds[i + 1].events |= POLLOUT;
        		}

        		if(poll(fds, fdcount, this->POLL_TIMEOUT))
        		{
        			// CHECK POLLING RESULTS
        			clientSock->setSocket(accept(this->getSocket(),
        						     (sockaddr*) &client,
        						     &clientSize));

        			if(clientSock->getSocket() != -1 && clientSock->getSocket() != 0)
        			{
        			}
        		}
        		free(fds);
        		delete clientSock;
        	}

        */	return true;
        }
/*
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

                                std::shared_ptr<TCPClientSocket<TCPSock>> client(new TCPClientSocket<TCPSock>());
                                client->setSocket(sock);
                                client->setHint(client_addr);
                                this->spawnWorker(client);

                            }
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
*/
        bool connect()
        {
        	return true;
        }

        bool disconnect()
        {
        	return true;
        }

        bool reconnect()
        {
        	return true;
        }

        bool alertServer(int command)
        {
        	return true;
        }

        bool spawnWorker(std::shared_ptr<TCPClientSocket<TCPSock>> client)
        {
		//std::shared_ptr<LoginWorker<TCPSock>> loginWorker(new LoginWorker<TCPSock>(this, client));
		//std::shared_ptr<std::thread> loginWorkerThread = std::make_shared<std::thread>([loginWorker]()
		//{
		//	loginWorker->run();
		//});
		//loginWorkerThread->detach();
		//this->addConnection(client);

        	return true;
        }

        int getID()
        {
        	return this->id;
        }

        void setID(int id)
        {
        	this->id = id;
        }

        ServerStatus getStatus()
        {
        	return this->status;
        }

        void setStatus(ServerStatus status)
        {
        	this->status = status;
        }

        std::mutex* getMutex()
        {
        	return &(this->mtx);
        }



        /*
		TCPServerSocket(char* ip, int port, int id);
		~TCPServerSocket();

		bool initialize(char* ip, int port);
		bool run();
        bool listen();
		bool connect();
		bool disconnect();
		bool reconnect();
		bool alertServer(int command);
		bool spawnWorker(std::shared_ptr<TCPClientSocket<TCPSock>> client);

		int getID();
		void setID(int id);

		ServerStatus getStatus();
		void setStatus(ServerStatus status);

		std::mutex* getMutex();
*/
	private:
		ServerStatus status;
		std::mutex mtx;
		int id;
        char* ip;
        int port;
};

#endif
