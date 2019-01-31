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
	if(this->length > 0)
	{
		free(this->bytes);
	}
}

void Packet::setBytes(byte* bytes, int length)
{
	this->bytes = bytes;
	this->length = length;
}

