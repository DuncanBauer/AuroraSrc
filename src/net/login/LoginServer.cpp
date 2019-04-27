#include "LoginServer.h"
#include "../sockets/TCPClientSocket.h"
#include "../../Master.h"

#include <iterator>
#include <mutex>
#include <poll.h>
#include <algorithm>
#include <memory>
#include <iostream>
#include <cerrno>

LoginServer::LoginServer(char* ip, int port, Master* master, int id) : GenericMapleServer(ip, port, master, id)
{
//	std::cout << "LoginServer constructor called" << '\n';
}

LoginServer::~LoginServer()
{
//	std::cout << "LoginServer destructor called" << '\n';
}

bool LoginServer::run()
{
	// Run until shutdown command is sent
//	while(true)
//	{	
		// Reads and executes server commands
		if(this->getServerAlertQueue()->size() > 0)
		{
			std::for_each(this->getConnections()->begin(), this->getConnections()->end(), [](auto connection)
			{
				connection.second->join();
				std::cout << "Loginworkerthread closed\n";
			});
			
			std::cout << "CMD: exit loginserver\n";
//			break;
		}

		// Set up for new connection
		sockaddr_in client_addr;
		socklen_t clientSize = sizeof(client_addr);

		struct pollfd *fds;
		int fdcount = this->getConnectionsLength() + 1;
		
		fds = (pollfd*)malloc(sizeof(struct pollfd) * fdcount);
		fds[0].fd = this->getSocket();
		fds[0].events = POLLIN | POLLOUT;
		
		int j = 0;
		Connections* temp = this->getConnections();
		std::for_each(temp->begin(), temp->end(), [temp, &fds, &j](auto connection) 
		{
			fds[j + 1].fd = connection.first->getSocket();
			fds[j + 1].events = POLLIN | POLLOUT;
			j++;
		});

//		if(poll(fds, fdcount, this->POLL_TIMEOUT))
//		{
			char host[NI_MAXHOST];
			char svc[NI_MAXSERV];
			int sock = accept(this->getSocket(),
				         (sockaddr*) &client_addr, 
					 &clientSize);
			
			if(sock > -1)
			{
				std::shared_ptr<TCPClientSocket> client(new TCPClientSocket());
				
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

	/*		
				char str[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &(client->getHint()->sin_addr), str, INET_ADDRSTRLEN);
				
				std::cout << "TCPClientSocket connected" << '\n';
				std::cout << "Port: " << client->getHint()->sin_port << '\n';
				std::cout << "IP: " << str << '\n';
	
	*/
				PacketStream ps;
				ps.setPacket(MaplePacketCreator::getHandshake());
				byte* arr;
				arr = (byte*)malloc(sizeof(byte) * ps.getPacket().length + 1);
				ps.nullTermBytes(arr);
				std::cout << arr << '\n';
				std::cout << ps.getByteStream().str() << '\n';
				std::cout << ps.getByteStreamHex().str() << '\n';

				client->setSocket(sock);
				client->setHint(client_addr);
				std::cout << "length: " << ps.getPacket().length << '\n';
				errno = 0;

				char msg[ps.getPacket().length + 1];
				ps.getByteStream().str().copy(msg, ps.getPacket().length + 1);
				msg[ps.getPacket().length] = '\0';

				result = send(client->getSocket(), arr, ps.getPacket().length+1, 0);
				std::cout << "TCPClientSocket Send result: " << result << '\n';
				if(result == -1)
				{
					std::cout << "TCPClientSocket Errno: " << errno << '\n';
				}
	
	
				byte buff[512];
				memset(buff, 0, 512);
				int bytesRecv = recv(client->getSocket(), buff, 512, 0);	
				if(bytesRecv)
				{
					std::cout << "Bytes available: " << bytesRecv << '\n';
					std::cout << "Data: " << buff << '\n';
				}
		
	//			std::cout << "TCPClientSocket Socket: " << client->getSocket() << '\n';
	//			std::cout << "Socket: " << sock << '\n';

				this->spawnWorker(client); 
			}
//		}
		free(fds);
//	}
	this->disconnect();
	return true;
}

bool LoginServer::connect()
{
	return true;
}

bool LoginServer::disconnect()
{
	std::cout << "Login server shutting down" << '\n';
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

	std::shared_ptr<std::thread> loginWorkerThread = std::make_shared<std::thread>([this, client]() { 
		LoginWorker loginWorker = LoginWorker(this, client);
//		loginWorker.run();
	});	
	loginWorkerThread->join();
	this->addConnection(client, loginWorkerThread);
	
	
	
	//workers.get()->emplace(workers.get()->size(), std::make_shared<LoginWorker>(loginWorker));
	
	
	return true;
}


