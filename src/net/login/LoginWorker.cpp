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

void LoginWorker::run(Client* client)
{
	while(true)
	{
		byte buff[512];
		memset(buff, 0, 512);

		int bytesRecv = recv(client->getSocket(), buff, 512, 0);
		if(bytesRecv)
		{
			std::cout << "# Bytes: " << bytesRecv << '\n';
			std::cout << "Data: " << buff << '\n';
		}

	}
}
