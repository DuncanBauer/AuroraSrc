#ifndef WORLD_H
#define WORLD_H

#include "channel/ChannelServer.h"
#include "login/LoginServer.h"

using Channels = std::vector<std::shared_ptr<ChannelServer>>;


class World
{
	public:
		World();
		World(Master*_master, int id, int channelCount);
		~World();
		
		Master* getMaster();

		void start();
		void shutdown();
		void restart();
		
		void startChannel(int id);
		void shutdownChannel(int id);
		void restartChannel(int id);

		int getID();
		void setID(int id);
		int getStatus();
		void setStatus(int i);
		
		int getChannelsOnline();
		int getChannelCount();
		void setChannelCount(int i);

		void addChannel(std::shared_ptr<ChannelServer> channel);
		bool removeChannel(std::shared_ptr<ChannelServer> channel);

	private:
		Master* master;
		int id;
		int status;
		int channelCount;
		std::unique_ptr<Channels> channels;
};

#endif
