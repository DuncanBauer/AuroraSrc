#ifndef TCPServerSocket_H
#define TCPServerSocket_h

#include <vector>
#include <iterator>
#include <thread>

#include <poll.h>

//#include "TCPSocket.h"
#include "../packets/PacketHandler.h"
#include "../../client/Client.h"


class TCPServerSocket: public TCPSocket 
{
    public:
	const int POLL_TIMEOUT = 3;

	TCPServerSocket();
	virtual ~TCPServerSocket();
	
	virtual void run();

	int getConnectionsLength();
	std::vector<Client*> getConnections();
	
	void addConnection(Client* client);
	void removeConnection(Client* client);

    private:
	std::vector<Client*> connections = std::vector<Client*>();
	void pruneConnections();
};

#endif
