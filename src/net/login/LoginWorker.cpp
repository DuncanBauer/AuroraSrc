#include "LoginWorker.h"
#include <iostream>

LoginWorker::LoginWorker()
{
	this->client = nullptr;
}

LoginWorker::LoginWorker(Client* client)
{
	this->client = client;
}

LoginWorker::~LoginWorker()
{
}

void LoginWorker::run(Client* mclient)
{
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
	handler.write(arr2, 3);
			
	byte b = 8;
	handler.write(b);
	send(mclient->getSocket(), handler.nullTermBytes(), handler.getPacket()->length + 1, 0);
	std::cout << handler.getByteStreamHex().str().c_str() << '\n';

	while(true)
	{
		byte buff[512];
		memset(buff, 0, 512);

		int bytesRecv = recv(mclient->getSocket(), buff, 512, 0);
		if(bytesRecv)
		{
			std::cout << "# Bytes: " << bytesRecv << '\n';
			std::cout << "Data: " << buff << '\n';
		}
	}
}
