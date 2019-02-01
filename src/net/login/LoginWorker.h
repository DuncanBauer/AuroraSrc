#ifndef LOGINWORKER_H
#define LOGINWORKER_H

#include <iostream>

#include "../packets/PacketHandler.h"
#include "../../client/Client.h"

class LoginWorker
{
	public:
		LoginWorker();
		LoginWorker(Client* client);
		~LoginWorker();
		
		static void run(Client* mclient);

	private:
		Client* client;
};

#endif
