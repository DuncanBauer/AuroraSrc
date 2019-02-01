#include "LoginServer.h"

LoginServer::LoginServer()
{
}

LoginServer::~LoginServer()
{
}

void LoginServer::run()
{
	while(true)
	{	
		//std::cout << "RUNNING LOGIN SERVER" << '\n';
		sockaddr_in client;
		socklen_t clientSize = sizeof(client);
	//	char host[NI_MAXHOST];
	//	char service[NI_MAXSERV];

		Client* mclient = new Client();

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
		std::cout << this->POLL_TIMEOUT << '\n';
		if(poll(fds, fdcount, this->POLL_TIMEOUT))
		{
			std::cout << "POLLING LOGIN SERVER" << '\n';
			// CHECK POLLING RESULTS
			mclient->setSocket(accept(this->getSocket(),
					         (sockaddr*) &client,
						 &clientSize));

			std::cout << mclient->getSocket() << '\n';
			
			if(mclient->getSocket() != -1 && mclient->getSocket() != 0)
			{
				// Spawn client on new thread
				std::cout << "Client connected" << '\n';
		
				//LoginWorker* loginWorker = new LoginWorker(mclient);
				
				//std::thread loginWorkerThread(loginWorker->run, mclient);
				
				//unsigned char buff[4096];
				//memset(buff, 0, 4096);
				
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
				send(mclient->getSocket(), handler.getPacket()->bytes, handler.getPacket()->length + 1, 0);
				
				std::cout << handler.getByteStreamHex().str().c_str() << '\n';
			
				this->addConnection(mclient);
			}
		}
		else
		{
			//std::cout << "NO POLL" << '\n';
		}
		free(fds);

		// Handle connected clients here
		// check if theyre alive
		// disconnect if dead after certain amount of time
		// remove socket from connection vector
	}
}
