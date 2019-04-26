#include "Master.h"

#include "tools/fileIO/ConfigParser.h"

#include <algorithm>
#include <unistd.h>

Master::Master(int worldCount)
{
	try
	{	
		ConfigParser configparser = ConfigParser();
		std::map<std::string, std::string> config = configparser.getValuesFromFile("master.conf");
		this->worldCount = worldCount;
		this->serverAlertQueue.reset(new AlertQueue());
		this->worlds.reset(new Worlds());

		char cstr[config["ip"].size() + 1];
		config["ip"].copy(cstr, config["ip"].size() + 1);
		cstr[config["ip"].size() - 1] = '\0';
		
		std::cout << "Launching login server" << '\n';
		this->loginServer.reset(new LoginServer(cstr, std::stoi(config["loginserver.port"]), this, 0));
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception thrown" << '\n';
	}
}

Master::~Master()
{
}

bool Master::initialize()
{
	return true;
}

void Master::run()
{
	using namespace std::chrono_literals;

	try
	{
		//this->loginServer.reset(new LoginServer(this->IP, 8484, std::make_shared<Master>(this), 1984));
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception thrown in Master::run" << '\n';
	}//this->loginServer->run();
	// Create and launch login server thread	
	std::future<bool> future = std::async(std::launch::async, &LoginServer::run, this->loginServer.get());
/*	for(int i = 0; i < master->getWorldCount(); ++i)
	{
		std::cout << "Launching world " << i << '\n';
		World* world = new World(master, i, 3);
		for(int j = 0; j < world->getChannelCount(); ++j)
		{
			std::cout << "    Launching channel " << j << " on world " << i << '\n';
			std::thread channelServerThread(&launchChannelServer, master, world, j, 7575 + j + (20 * 1));
			channelServerThread.detach();
		}
		master->addWorld(world);
	}
	
*/

	char command[256];
	while(true)
	{
	//	if(future.wait_for(0ms) == std::future_status::ready)
	//	{
	//		std::cout << "Login Thread closed" << '\n';
	//	}
		std::cout << "> ";
		std::cin.getline(command, 256);

		if(strcmp(command,"exit") == 0)
		{
			std::lock_guard<std::mutex> lock(this->mutex);
			this->serverAlertQueue->push(1);
			break;
		}
	}

	sleep(3);
}

void Master::shutdown()
{	
	try
	{
		for(unsigned int i = 0; i < this->serverAlertQueue.get()->size(); ++i)
		{
			this->serverAlertQueue.get()->pop();
		}
		this->worlds.get()->clear();
		this->loginServer.reset();
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception thrown" << '\n';
	}

}

AlertQueue* Master::getServerAlertQueue()
{
	return this->serverAlertQueue.get();
}

LoginServer* Master::getLoginServer()
{
	return this->loginServer.get();
}

Worlds* Master::getWorlds()
{
	return this->worlds.get();
}

int Master::getWorldCount()
{
	return this->worldCount;
}

World* Master::getWorld(int id)
{
	if(id < this->worldCount)
	{
		return this->worlds.get()->at(id);
	}
	else
	{
		return nullptr;
	}
}

bool Master::checkChannelsOnline()
{
	std::for_each(this->worlds.get()->begin(), this->worlds.get()->end(),[](World* world)
	{
		if(world->getChannelsOnline() > 0)
		{
			return false;
		}
	});
	return true;
}

void Master::startWorld(int id)
{
	this->worlds.get()->at(id)->start();
}

void Master::shutdownWorld(int id)
{
	this->worlds.get()->at(id)->shutdown();
}

void Master::restartWorld(int id)
{
	this->worlds.get()->at(id)->restart();
}

void Master::addWorld(World* world)
{
	this->worlds.get()->push_back(world);
}

void Master::removeWorld(World* world)
{
	/*
	auto it = this->worlds.begin();
	while(it != this->worlds.end())
	{
		if(world->getID() == *it.getID())
		{
			break;
		}
	}
	if(it != this->worlds.end())
	{
		this->worlds.erase(it);
	}
	*/
}


/*
void Master::launchChannelServer(std::unique_ptr<Master> master, std::unique_ptr<World> world, int id, int port)
{
	std::unique_ptr<ChannelServer> channelServer(new ChannelServer(master, id));
	channelServer.get()->initialize(IP, port);
	world.get()->addChannel(channelServer);
	channelServer.get()->run();
}
*/
