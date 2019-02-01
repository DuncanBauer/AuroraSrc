#include "net/login/LoginServer.h"

int main(int argc, char* argv[])
{
	LoginServer sock = LoginServer();
	sock.initialize("0.0.0.0", 8484);
	sock.run();

	return 0;
}
