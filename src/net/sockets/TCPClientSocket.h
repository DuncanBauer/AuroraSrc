#ifndef CLIENT_H
#define CLIENT_H


//class LoginWorker;
//class ChannelWorker;

template <class TCPSock>
class TCPClientSocket : public TCPSock
{
	public:
		TCPClientSocket();
		TCPClientSocket(int sock);
		~TCPClientSocket();

		bool closeSocket();
		void disconnect();
};


#endif
