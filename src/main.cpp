#include "Master.h"


int main(int argc, char* argv[])
{
	std::shared_ptr<Master> master(new Master(1));
	master->loginServer.reset(new LoginServer(master->IP, 8484, master, 0));
	master->run();
	master->shutdown();
	return 0;
}


