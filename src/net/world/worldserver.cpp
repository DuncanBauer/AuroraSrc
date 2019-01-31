#include "../sockets/TCPServerSocket.h"
#include "../packets/PacketHandler.h"
#include "../../tools/hexTool.h"

int main(int argc, char* argv[]) 
{
	
	TCPServerSocket sock = TCPServerSocket();
	sock.initialize("0.0.0.0", 8490);

	while(true)
	{
		//std::cout << "Checking connections" << '\n';
		if(sock.waitOnConnections(1, 0) != 1)
		{
			continue;
		}
		if(sock.getConnectionsLength() > 0)
		{
			//std::cout << sock.getConnectionsLength() << '\n';		
			unsigned char buff[4096];
			auto it = (sock.getConnections()).begin();
			while(it != (sock.getConnections()).end())
			{
				memset(buff, 0, 4096);

				int bytesRecv = recv((*it)->getSocket(), buff, 4096, 0);
//				if(bytesRecv == -1)
//				{
//					auto last = next(it);
//					sock.removeConnection(*last);
//					std::cerr << "Problem with connection" << '\n';
//					break;
//				}
//				if(bytesRecv == 0)
//				{
//					auto last = next(it);
//					close((*it)->getSocket());
//					sock.removeConnection(*last);
//					std::cout << "Client disconnected" << '\n';
//				}
//
				if(bytesRecv > 0)
				{
					std::cout << "BytesRecv: " << bytesRecv << '\n';
					std::cout << "Received: " << buff << '\n';
				}

				//Packet p = Packet(reinterpret_cast<const unsigned char*>("0d003e00000046727add523078c208"), 30);
				//const char* packet = "0d003e00000046727add523078c208";
				//const char* hex = PacketToHex(p).str().c_str();
				//std::cout << hex << '\n';
				
				//send((*it)->getSocket(), reinterpret_cast<const char*>(p.getBytes()), p.getLength(), 0);
				//send((*it)->getSocket(), "0x00", (int)strlen("0x00"), 0);

				next(it); 
			}			
		}
	}






















//	while(sock.listening() == 1)
//	{
//		std::cout << "listening" << '\n';
//	}

	/*
	// Create Socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if(listening == -1)
        {
	        std::cerr << "Can\'t create socket" << '\n';
	        return -1;
	}

	// Bind socket to ip/port
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(54000);
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

	if(bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
	{
		std::cerr << "Can\'t bind to PORT/IP" << '\n';
		return -2;
	}

	
	if(listen(listening, SOMAXCONN) == -1)
	{
		std::cerr << "Can\'t listen" << '\n';
		return -3;
	}

	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	char host[NI_MAXHOST];
	char svc[NI_MAXSERV];

	int clientSocket = accept(listening,
				  (sockaddr*)&client,
				  &clientSize);

	if(clientSocket == -1)
	{
		std::cerr << "Problem connecting with client" << '\n';
		return -4;
	}

	close(listening);

	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo((sockaddr*)&client,
				 sizeof(client),
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
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on " << ntohs(client.sin_port) << '\n';
	}

	char buff[4096];
	while(true)
	{
		memset(buff, 0, 4096);

		int bytesRecv = recv(clientSocket, buff, 4096, 0);
		if(bytesRecv == -1)
		{
			std::cerr << "Problem with connection" << '\n';
			break;
		}
		if(bytesRecv == 0)
		{
			std::cout << "Client disconnected" << '\n';
			break;
		}

		std::cout << "Received: " << buff << '\n';
		send(clientSocket, buff, bytesRecv + 1, 0);
	}
	close(clientSocket);
	*/
}
