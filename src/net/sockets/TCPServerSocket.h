#ifndef TCPServerSocket_H
#define TCPServerSocket_h

#include <list>

#include "TCPSocket.h"
#include "../packets/PacketHandler.h"

class TCPServerSocket: public TCPSocket 
{
    public:
	TCPServerSocket();
	~TCPServerSocket();

	int waitOnConnections(int milliTimeout, int secTimeout);
	
	int getConnectionsLength();
	std::list<TCPSocket*> getConnections();
	void removeConnection(TCPSocket* socket);

    private:
	std::list<TCPSocket*> connections = std::list<TCPSocket*>();
	void pruneConnections();
};

#endif
