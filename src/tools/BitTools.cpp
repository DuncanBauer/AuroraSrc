#include "BitTools.h"

byte BitTools::rollLeft(byte in, int count) {
    int tmp = (int) in & 0xFF;
    tmp = tmp << (count % 8);
    return (byte) ((tmp & 0xFF) | (tmp >> 8));
}

byte BitTools::rollRight(byte in, int count) {
    int tmp = (int) in & 0xFF;
    tmp = (tmp << 8) >> (count % 8);

    return (byte) ((tmp & 0xFF) | (tmp >> 8));
}

void BitTools::multiplyBytes(byte * in, byte * out, int count, int mul)
{
	for(int x = 0; x < count * mul; ++x)
	{
		out[x] = in[x % count];
	}
}
