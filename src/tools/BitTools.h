#ifndef BITTOOLS_H
#define BITTOOLS_H

#include "Packet.h"

namespace BitTools
{
    byte rollLeft(byte in, int count);
    byte rollRight(byte in, int count);
};

#endif
