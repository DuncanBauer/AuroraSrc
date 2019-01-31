#ifndef TCPServerSocket_H
#define TCPServerSocket_h

#include "TCPSocket.h"
#include "../packets/Packet.h"
#include <list>

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
