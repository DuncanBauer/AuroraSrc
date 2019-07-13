#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H


//class LoginWorker;
//class ChannelWorker;

template <class TCPSock>
class TCPClientSocket : public TCPSock
{
	public:
	TCPClientSocket()
	{
	}
	
	TCPClientSocket(int sock) : TCPSock(sock)
	{
	}
	
	~TCPClientSocket()
	{
	}

	bool closeSocket()
	{
		return true;
	}

	void disconnect()
	{
	}
	
	
	/*	TCPClientSocket();
		TCPClientSocket(int sock);
		~TCPClientSocket();

		bool closeSocket();
		void disconnect();
	*/
	};


#endif
