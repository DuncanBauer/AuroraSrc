#include "PacketStream.h"

PacketStream::PacketStream()
{
	this->packet = Packet();
}

PacketStream::~PacketStream()
{
}

Packet PacketStream::getPacket()
{
	return packet;
}

void PacketStream::setPacket(Packet packet)
{
	this->packet = packet;
}

std::ostringstream PacketStream::getByteStream()
{
	std::ostringstream str;
	for(int i = 0; i < this->packet.length; ++i)
	{
		str << this->packet.bytes[i] << ' ';
	}
	return str;
}

std::ostringstream PacketStream::getByteStreamHex()
{
	std::ostringstream str;
	for(int i = 0; i < this->packet.length; ++i)
	{
		str << std::hex << (unsigned int)this->packet.bytes[i] << std::dec << ' ';
	}
	return str;
}

void PacketStream::writeByte(byte b)
{
	this->packet.bytes.push_back(b);
	++(this->packet.length);
}

byte PacketStream::readByte()
{
	if(this->packet.length > 0)
	{
		auto val = this->packet.bytes.begin();
		byte ret = *val;
		this->packet.bytes.erase(val);
		return ret;
	}

	return '\0';
}

void PacketStream::write(byte b)
{
	this->writeByte(b);
}

void PacketStream::write(const char* b)
{
	for(unsigned int i = 0; i < strlen(b); ++i)
	{
		this->writeByte(b[i]);
	}
}

void PacketStream::write(byte* b, int len)
{
	for(int i = 0; i < len; ++i)
	{
		this->writeByte(b[i]);
	}
}

void PacketStream::write(int b)
{
	this->writeByte((byte)(b & 0xFF));
	this->writeByte((byte)((b >> 8) & 0xFF));
	this->writeByte((byte)((b >> 16) & 0xFF));
	this->writeByte((byte)((b >> 24) & 0xFF));	
}

void PacketStream::write(_short b)
{
	this->writeByte((byte)(b & 0xFF));
	this->writeByte((byte)((b >> 8) & 0xFF));
}

void PacketStream::write(_double b)
{
	this->writeByte((byte)(b & 0xFF));
	this->writeByte((byte)((b >> 8) & 0xFF));
	this->writeByte((byte)((b >> 16) & 0xFF));
	this->writeByte((byte)((b >> 24) & 0xFF));
	this->writeByte((byte)((b >> 32) & 0xFF));
	this->writeByte((byte)((b >> 40) & 0xFF));
	this->writeByte((byte)((b >> 48) & 0xFF));
	this->writeByte((byte)((b >> 56) & 0xFF));
}

void PacketStream::write(std::string b)
{
	for(unsigned int i = 0; i < b.length(); ++i)
	{
		this->write((byte)b[i]);
	}
}

int PacketStream::readInt()
{
	byte b1 = this->readByte();
	byte b2 = this->readByte();
	byte b3 = this->readByte();
	byte b4 = this->readByte();

	return (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
}

_short PacketStream::readShort()
{
	byte b1 = this->readByte();
	byte b2 = this->readByte();

	return (b2 << 8) + b1;
}

_double PacketStream::readDouble()
{
	_double b1 = this->readByte();
	_double b2 = this->readByte();
	_double b3 = this->readByte();
	_double b4 = this->readByte();
	_double b5 = this->readByte();
	_double b6 = this->readByte();
	_double b7 = this->readByte();
	_double b8 = this->readByte();

	return (b8 << 56) + (b7 << 48) + (b6 << 40) + (b5 << 32) + (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
}

std::string PacketStream::readString(int size)
{
//	byte* bytes = (byte*)std::malloc(size);
	std::ostringstream str;
	for(int i = 0; i < size; ++i)
	{
	//	bytes[i] = this->readByte();
		str << this->readByte();
	}
//	return bytes;
	return str.str();
}

byte* PacketStream::nullTermBytes()
{
/*
	byte* temp = (byte*) malloc(this->packet.length + 1);
	for(int i = 0; i < this->packet.length; ++i)
	{
		temp[i] = this->packet.bytes[i];
	}
	temp[this->packet.length] = '\0';

	return temp;
*/
}

void PacketStream::skip(int n)
{
	if(n > this->packet.length)
	{
		n = this->packet.length;
	}

	for(int i = 0; i < n; ++i)
	{
		this->readByte();
	}
}

byte* PacketStream::seek(int n)
{
	if(n > this->packet.length)
	{
		n = this->packet.length;
	}

	byte arr[n];
	for(int i = 0; i < n; ++i)
	{
		arr[i] = this->readByte();
	}

	return arr;
}
