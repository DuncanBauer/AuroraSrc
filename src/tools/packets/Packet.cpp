#include "Packet.h"

Packet::Packet()
{
	this->length = 0;
}

Packet::Packet(std::vector<byte> bytes, int length)
{
	this->bytes = bytes;
	this->length = length;
}

Packet::~Packet()
{
	if(!this->bytes.empty())
	{
		this->bytes.clear();
	}
}

void Packet::setBytes(std::vector<byte> bytes, int length)
{
	this->bytes = bytes;
	this->length = length;
}

