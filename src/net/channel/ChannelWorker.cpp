#include "ChannelWorker.h"

ChannelWorker::ChannelWorker()
{
}

ChannelWorker::ChannelWorker(std::shared_ptr<ChannelServer> channelServer, std::shared_ptr<Client> client)
{
	this->channelServer = channelServer;
	this->client = client;
}

ChannelWorker::~ChannelWorker()
{
}

void ChannelWorker::initialize()
{
}

void ChannelWorker::run()
{
}

void ChannelWorker::connect()
{
}

void ChannelWorker::disconnect()
{
}

void ChannelWorker::reconnect()
{
}

void ChannelWorker::stop()
{
}
