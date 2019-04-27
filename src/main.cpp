#include "Master.h"


int main(int argc, char* argv[])
{
/*
	while(true)
	{
	//	if(future.wait_for(0ms) == std::future_status::ready)
	//	{
	//		std::cout << "Login Thread closed" << '\n';
	//	}
		//if(strcmp(command,"exit") == 0)
		std::string cmd;
		std::cout << "> ";
		std::getline(std::cin, cmd);
		if(cmd == "exit")
		{
			break;
		}
	}
*/
	Master* master = new Master(1);
	master->run();
	master->shutdown();
	delete master;
	return 0;
}


