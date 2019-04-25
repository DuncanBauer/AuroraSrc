#include "Master.h"


int main(int argc, char* argv[])
{
	Master* master = new Master(1);
	master->run();
	master->shutdown();
	delete master;
	return 0;
}


