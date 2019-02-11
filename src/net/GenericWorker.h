#ifndef GENERICWORKER_H
#define GENERICWORKER_H

class GenericWorker
{
	public:
		virtual void initialize() = 0;
		virtual void run() = 0;
		virtual void connect() = 0;
		virtual void disconnect() = 0;
		virtual void reconnect() = 0;
		virtual void stop() = 0;
};

#endif
