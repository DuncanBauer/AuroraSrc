#ifndef MAPLEAESOFB_H
#define MAPLEAESOFB_H

#include "../../tools/packets/Packet.h"

class MapleAESOFB
{
	public:
		MapleAESOFB();
		~MapleAESOFB();

		bool checkPacketHeader(int header);
	private:
		byte* iv;
};

#endif
