#include "TCPServerSocket.h"

TCPServerSocket::TCPServerSocket()
{
}

TCPServerSocket::~TCPServerSocket()
{
	this->connections.clear();
	close(this->sock);
}

int TCPServerSocket::waitOnConnections(int milliTimeout, int secTimeout)
{
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	TCPSocket* clientSock = new TCPSocket();

	if(milliTimeout == 0 && secTimeout == 0)
	{
		clientSock->setSocket(accept(this->sock,
					    (sockaddr*) &client,
					    &clientSize));
	}
	else
	{
		fd_set fds;
		struct timeval tv;
		
		tv.tv_sec = secTimeout;
		tv.tv_usec = milliTimeout;
		FD_ZERO(&fds);
		FD_SET(this->getSocket(), &fds);
		
		select(this->getSocket() + 1, &fds, NULL, NULL, &tv);
		if(FD_ISSET(this->getSocket(), &fds))
		{
			//std::cout << "setting socket" << '\n';
			clientSock->setSocket(accept(this->sock,
						     (sockaddr*) &client,
						     &clientSize));
		}
	}

	if(clientSock->getSocket() == -1)
	{
		//std::cerr << "No connection established" << '\n';
		return -1;
	}
	else if(clientSock->getSocket() == 0)
	{
		//std::cerr << "Socket not set" << '\n';
		return -2;
	}
	else
	{
		std::cout << "Socket Connected" << '\n';
		memset(host, 0, NI_MAXHOST);
		memset(service, 0, NI_MAXSERV);

		//int result = getnameinfo((sockaddr*) &client,
		//			 clientSize,
		//			 host,
		//			 NI_MAXHOST,
		//			 service,
		//			 NI_MAXSERV,
		//			 0);

		unsigned char buff[4096];
		memset(buff, 0, 4096);
		
		/*
		send(clientSock->getSocket(), "0x0", (int)strlen("0x0"), 0);
		int bytesRecv = recv(clientSock->getSocket(), buff, 4096, 0);
		if(bytesRecv)
		{
			std::cout << "Bytes: " << buff << '\n';
		}
		else
		{
			std::cout << "No bytes\?";
		}

		if(result)
		{
			std::cout << host << " connected on " << service << '\n';
		}
		*/

//		byte bytes[15] = {0x0d, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x46, 0x72, 0x7a, 0xdd, 0x52, 0x30, 0x78, 0xc2, 0x08};
//		for(int i = 0; i < 15; i++)
//		{
//			std::cout << bytes[i] << ' ';
//		}

		//Packet p = Packet(reinterpret_cast<const unsigned char*>("0d003e00000046727add523078c208"), 30);
		//const byte* bytes = stringToBytes("0d003e00000046727add523078c208", 30);


		PacketHandler handler = PacketHandler();
		_short s = 0x0d;
		handler.write(s);
		s = 62;
		handler.write(s);
		s = 0;
		handler.write(s);
		handler.write(s);
		
		byte b1 = (byte)(rand() % 255);
		byte b2 = (byte)(rand() % 255);
		byte b3 = (byte)(rand() % 255);
		byte arr[3] = {b1,b2,b3};
		byte arr2[3] = {b3,b2,b1};
		handler.write(arr, 3);
		std::cout << handler.getByteStreamHex().str().c_str() << '\n';
		handler.write(arr2, 3);
		std::cout << handler.getByteStreamHex().str().c_str() << '\n';
		byte b = 8;
		handler.write(b);
		std::cout << handler.getByteStreamHex().str().c_str() << '\n';
		send(clientSock->getSocket(), handler.getPacket()->bytes, handler.getPacket()->length + 1, 0);
		
		
		this->connections.push_front(clientSock);
	}
	clientSock = NULL;
	return 1;
}

int TCPServerSocket::getConnectionsLength()
{
	return this->connections.size();
}


void TCPServerSocket::removeConnection(TCPSocket* socket)
{
	this->connections.remove(socket);
}


std::list<TCPSocket*> TCPServerSocket::getConnections()
{
	return this->connections;
}

void TCPServerSocket::pruneConnections()
{
	for(auto it = this->connections.begin(); it != this->connections.end(); ++it)
	{
		//if(it == 0 || it == -1)

	}
}
