#include "Packet.h"

Packet::Packet()
{
}

Packet::Packet(byte* bytes, int length)
{
	this->bytes = bytes;
	this->length = length;
}

Packet::~Packet()
{
}

void Packet::setBytes(byte* bytes, int length)
{
	this->bytes = bytes;
	this->length = length;
}

