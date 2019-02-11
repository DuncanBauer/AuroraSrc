#ifndef MAPLECODEC_H
#define MAPLECODEC_H

#include "../../tools/packets/PacketStream.h"

class MapleCodec
{
	public:
		MapleCodec();
		~MapleCodec();
		
		void encode(PacketStream packet);
		void decode(PacketStream packet);

	private:
		int status;
};

#endif
