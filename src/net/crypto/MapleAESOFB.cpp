#include "MapleAESOFB.h"

MapleAESOFB::MapleAESOFB()
{
}

MapleAESOFB::~MapleAESOFB()
{
}

bool MapleAESOFB::checkPacketHeader(int header)
{
	byte* bytes = (byte*)malloc(2);
	bytes[0] = (byte) ((header >> 24) & 0xFF);
	bytes[1] = (byte) ((header >> 16) & 0xFF);

	return ((((bytes[0] ^ this->iv[2]) & 0xFF) == ((62 >> 8) & 0xFF)) && (((bytes[1] ^ this->iv[3]) & 0xFF) == (62 & 0xFF)));
}
