#include "World.h"

#include <algorithm>

World::World() : id(-1), status(0), channelCount(0)
{
}

World::World(Master* master, int id, int channelCount) : master(master), id(id), status(0), channelCount(channelCount)
{
	this->master = master;
	this->setID(id);
	this->channelCount = channelCount;
	this->channels.reset(new Channels(this->channelCount));
}

World::~World()
{
	this->channels.get()->clear();
	this->channels.reset();
}

Master* World::getMaster()
{
	return this->master;
}

void World::start()
{
}

void World::shutdown()
{
}

void World::restart()
{
}

void World::startChannel(int id)
{
}

void World::shutdownChannel(int id)
{
}

void World::restartChannel(int id)
{
}

int World::getID()
{
	return this->id;
}

void World::setID(int id)
{
	this->id = id;
}

int World::getStatus()
{
	return this->status;
}

void World::setStatus(int i)
{
	this->status = i;
}

int World::getChannelsOnline()
{
	int i = 0;
	std::for_each(this->channels.get()->begin(), this->channels.get()->end(), [&i](std::shared_ptr<ChannelServer> channel)
	{
		if(channel.get()->getStatus() == 1)
		{
			++i;
		}
	});
	return i;
}

int World::getChannelCount()
{
	return this->channelCount;
}

void World::setChannelCount(int i)
{
	this->channelCount = i;
}

void World::addChannel(std::shared_ptr<ChannelServer> channel)
{
	this->channels.get()->push_back(channel);
}

bool World::removeChannel(std::shared_ptr<ChannelServer> channel)
{
	/*
	auto it = this->channels.begin();
	while(it != this->channels.end())
	{
		if(channel->getID() == *it.getID())
		{
			break;
		}
	}
	if(it != this->channels.end())
	{
		this->channels.erase(it);
	}
	*/
}
