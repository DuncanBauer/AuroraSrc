#include "Packet.h"

Packet::Packet()
{
	this->length = 0;
}

Packet::Packet(std::string bytes)
{
	std::copy(bytes.begin(), bytes.end(), std::back_inserter(this->bytes));
	this->length = bytes.size();
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

