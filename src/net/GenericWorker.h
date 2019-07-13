#ifndef GENERICWORKER_H
#define GENERICWORKER_H

class GenericWorker
{
	public:
		void initialize();
		void run();
		void connect();
		void disconnect();
		void reconnect();
		void stop();
};

#endif
