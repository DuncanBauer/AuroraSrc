#include "LoginWorker.h"
#include "LoginServer.h"

#include "../crypto/MapleCodec.h"

#include <queue>
#include <poll.h>

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
		int bytesRecv = 1;
		while(true)
		{
			struct pollfd *fds;
			int count = 1;
			fds = (pollfd*)malloc(sizeof(pollfd) * count);
			fds[0].fd = this->client->getSocket();
			fds[0].events = POLLIN;

			int res = poll(fds, count, this->POLL_TIMEOUT);
			if(res)
			{
				byte buff[512];
				memset(buff, 0, 512);
				bytesRecv = recv(client->getSocket(), buff, 512, 0);
				std::string temp = reinterpret_cast<char *>(buff);
				data = data + temp;
		
				// Ends reading when the packet is finished or the client disconnects
				if(bytesRecv == -1 || bytesRecv == 0)
				{
					std::cout << "End packet\n";
					break;
				}
			}
			else
			{
				break;
			}
		}

		// If the client has disconnected break the loop and let thread end
		if(bytesRecv == 0)
		{
			break;
		}

		// Decode the packet
		if(data.size() > 0)
		{
			Packet packet = Packet(data);
			std::cout << "Data: " << data << '\n';
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
