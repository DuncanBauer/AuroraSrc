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
		fds[0].events = POLLOUT | POLLIN;
		for(int i = 0; i < this->getConnectionsLength(); ++i)
		{
			fds[i + 1].fd = this->getConnections()[i]->getSocket();
			fds[i + 1].events = POLLOUT | POLLIN;
		}
		if(poll(fds, fdcount, this->POLL_TIMEOUT))
		{
			//std::cout << "POLLING LOGIN SERVER" << '\n';
			// CHECK POLLING RESULTS
			//mclient->setSocket(accept(this->getSocket(), (sockaddr*) &client, &clientSize));

			mclient->setSocket(accept(this->getSocket(),
					          (sockaddr*) &client, 
						  &clientSize));
		}

		if(mclient->getSocket() != -1 && mclient->getSocket() != 0)
		{
			// Spawn client on new thread
			std::cout << "Client connected" << '\n';
		
			LoginWorker* loginWorker = new LoginWorker(mclient);
			std::thread loginWorkerThread(&LoginWorker::run, mclient);
			loginWorkerThread.detach();

			//unsigned char buff[4096];
			//memset(buff, 0, 4096);
				
			this->addConnection(mclient);
		}
		free(fds);

		// Handle connected clients here
		// check if theyre alive
		// disconnect if dead after certain amount of time
		// remove socket from connection vector
	}
}
