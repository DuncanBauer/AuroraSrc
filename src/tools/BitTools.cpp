#include "BitTools.h"

byte  BitTools::rollLeft(byte in, int count) {
    int tmp = (int) in & 0xFF;
    tmp = tmp << (count % 8);
    return (byte) ((tmp & 0xFF) | (tmp >> 8));
}

byte BitTools::rollRight(byte in, int count) {
    int tmp = (int) in & 0xFF;
    tmp = (tmp << 8) >> (count % 8);

    return (byte) ((tmp & 0xFF) | (tmp >> 8));
}
