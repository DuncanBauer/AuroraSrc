#ifndef MASTER_H
#define MASTER_H

#include "net/World.h"

#include <mutex>
#include <queue>

using AlertQueue = std::priority_queue<int>;
using Worlds = std::vector<World*>;


class Master
{
	public:
		Master(int _worldCount);
		~Master();

		bool initialize();
		void run();
		void shutdown();

		AlertQueue* getServerAlertQueue();
		LoginServer* getLoginServer();
		Worlds* getWorlds();

		int getWorldCount();
		World* getWorld(int id);
		
		bool checkChannelsOnline();

		void startWorld(int id);
		void shutdownWorld(int id);
		void restartWorld(int id);

		void addWorld(World* world);
		void removeWorld(World* world);
	

		char* IP = "0.0.0.0";
		int worldCount;
		std::mutex mutex;
		std::unique_ptr<AlertQueue> serverAlertQueue;
		std::unique_ptr<LoginServer> loginServer;
		std::unique_ptr<Worlds> worlds;
};

#endif
