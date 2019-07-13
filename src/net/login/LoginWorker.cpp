#include "LoginWorker.h"

#include "LoginServer.h"

#include "../crypto/MapleCodec.h"

#include <queue>
//#include <poll.h>

/*
template <class TCPSock>
LoginWorker<TCPSock>::LoginWorker()
{
}

template <class TCPSock>
LoginWorker<TCPSock>::LoginWorker(LoginServer<TCPSock>* loginServer, std::shared_ptr<TCPClientSocket<TCPSock>> client)
{
	this->loginServer = loginServer;
	this->client = client;
}

template <class TCPSock>
LoginWorker<TCPSock>::~LoginWorker()
{
	this->client.reset();
	this->loginServer = NULL;
}

template <class TCPSock>
void LoginWorker<TCPSock>::initialize()
{
}

template <class TCPSock>
void LoginWorker<TCPSock>::run()
{
    /*
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

		// Loop until we receive complete packet or client disconnects
		std::string data = "";
		int bytesRecv = 1;
		while(true)
		{
			// Initialize file descriptor
			struct pollfd *fds;
			int count = 1;
			fds = (pollfd*)malloc(sizeof(pollfd) * count);
			fds[0].fd = this->client->getSocket();
			// RECV: So check for incoming data
			fds[0].events = POLLIN;

			// Check for data
			int res = poll(fds, count, this->POLL_TIMEOUT);
			// Data available to receive
			if(res)
			{
				// Grab data and append to rest of string
				byte buff[512];
				memset(buff, 0, 512);
				bytesRecv = recv(client->getSocket(), buff, 512, 0);
				std::string temp = reinterpret_cast<char *>(buff);
				data = data + temp;
				std::cout << "IN PROGRESS DATA (DEC): " << data << '\n';
				std::cout << "IN PROGRESS DATA (HEX): " << std::hex << data << std::dec << '\n';
				// Ends reading when the packet is finished or the client disconnects
				if(bytesRecv == -1 || bytesRecv == 0)
				{
					break;
				}
			}
			// No data to receive, break packet loop
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
			PacketStream ps;
			Packet packet = Packet(data);
			ps.setPacket(packet);
			std::ostringstream str = ps.getByteStreamHex();


			std::cout << "Packet Length: " << packet.length  << '\n';
			std::cout << "Raw Data: " << data << '\n';
			//std::cout << "Decoded: " << MapleCodec::decode(packet) << '\n';
			std::cout << "Raw HEX: " << str.str().c_str() << '\n';
			std::cout << "Raw DEC: " << ps.getByteStream().str().c_str();
		}

	}
	this->disconnect();

}

template <class TCPSock>
void LoginWorker<TCPSock>::connect()
{
}

template <class TCPSock>
void LoginWorker<TCPSock>::disconnect()
{
	this->loginServer->removeConnection(this->client);
	this->client.reset();
}

template <class TCPSock>
void LoginWorker<TCPSock>::reconnect()
{
}

template <class TCPSock>
void LoginWorker<TCPSock>::stop()
{
}
*/
