#include "LoginWorker.h"
#include "LoginServer.h"

#include "../crypto/MapleCodec.h"

#include <queue>

LoginWorker::LoginWorker()
{
}

LoginWorker::LoginWorker(LoginServer* loginServer, std::shared_ptr<TCPClientSocket> client)
{
	this->loginServer = loginServer;
	this->client = client;
}

LoginWorker::~LoginWorker()
{
	this->client.reset();
	this->loginServer = NULL;
}

void LoginWorker::initialize()
{
}

void LoginWorker::run()
{
	// Create and send handshake to launch client
	PacketStream ps;
	ps.setPacket(MaplePacketCreator::getHandshake());

	byte* arr;
	arr = (byte*)malloc(sizeof(byte) * ps.getPacket().length + 1);
	ps.nullTermBytes(arr);

	send(this->client->getSocket(), arr, ps.getPacket().length+1, 0);
	free(arr);

	// Listen for packets until we can't?
	while(true)
	{
		if(this->loginServer->getServerAlertQueue()->size() > 0)
		{
			std::cout << "CMD: exit loginworker\n";
			break;
		}

        // Receive entire packet
        std::string data = "";
        int bytesRecv = 0;
		while(true)
        {
    		byte buff[512];
    		memset(buff, 0, 512);
    	    bytesRecv = recv(client->getSocket(), buff, 512, 0);
            std::string temp = reinterpret_cast<char *>(buff);
            data = data + temp;
            std::cout << "Bytes recv: " << bytesRecv << '\n';
            // Ends reading when the packet is finished or the client disconnects
            if(bytesRecv == -1 || bytesRecv == 0)
            {
                std::cout << "End packet\n";
                break;
            }
		}

        // If the client has disconnected break the loop and let thread end
        if(bytesRecv == 0)
		{
			break;
		}

        if(data.size() > 0)
        {
            std::vector<byte> vec;
            Packet packet;
            std::copy(data.begin(), data.end(), std::back_inserter(vec));
            packet.bytes = vec;
            packet.length = vec.size();
            std::cout << "Data: " << data << "\n\n\n";
            std::cout << "Decoded: " << MapleCodec::decode(packet) << '\n';
        }

	}
	this->disconnect();
}

void LoginWorker::connect()
{
}

void LoginWorker::disconnect()
{
	this->loginServer->removeConnection(this->client);
	this->client.reset();
}

void LoginWorker::reconnect()
{
}

void LoginWorker::stop()
{
}
