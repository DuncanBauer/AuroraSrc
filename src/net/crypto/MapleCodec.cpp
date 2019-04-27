#include "MapleCodec.h"

MapleCodec::MapleCodec()
{
	this->status = 0;
}

MapleCodec::~MapleCodec()
{
}

void MapleCodec::encode(PacketStream packet)
{
}

void MapleCodec::decode(PacketStream packet)
{
/*	if(this->status == 0 && packet.getPacket().length > 4)
	{
		int header = packet.readInt();
		
	}
*/
}
