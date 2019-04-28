#ifndef MAPLECODEC_H
#define MAPLECODEC_H

#include "../../tools/Packet.h"

namespace MapleCodec
{
		byte * encode(Packet packet);
		byte * decode(Packet packet);
};

#endif
