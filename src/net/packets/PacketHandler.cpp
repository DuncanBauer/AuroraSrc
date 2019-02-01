#include "PacketHandler.h"

PacketHandler::PacketHandler()
{
	this->packet = Packet();
}

PacketHandler::~PacketHandler()
{
}

Packet* PacketHandler::getPacket()
{
	return &packet;
}

std::ostringstream PacketHandler::getByteStream()
{
	std::ostringstream str;
	for(int i = 0; i < this->packet.length; ++i)
	{
		str << (byte)this->packet.bytes[i] << ' ';
	}
	return str;
}

std::ostringstream PacketHandler::getByteStreamHex()
{
	std::ostringstream str;
	for(int i = 0; i < this->packet.length; ++i)
	{
		str << std::hex << (unsigned int)this->packet.bytes[i] << std::dec << ' ';
	}
	return str;
}

void PacketHandler::writeByte(byte b)
{
	if(this->packet.length == 0)
	{
		this->packet.bytes = (byte*)std::malloc(1);
		this->packet.bytes[0] = b;
		++this->packet.length;
	}
	else
	{
		byte* temp = (byte*)std::malloc(this->packet.length + 1);
		for(int i = 0; i < this->packet.length; ++i)
		{
			temp[i] = this->packet.bytes[i];
		}
		temp[this->packet.length] = b;
		++this->packet.length;
		//std::free(this->packet.bytes);
		this->packet.bytes = std::move(temp);
	}

}

byte PacketHandler::readByte()
{
	byte b = '\0';
	if(this->packet.length > 0)
	{
		b = this->packet.bytes[0];
		byte* temp = (byte*)malloc(this->packet.length - 1);
		for(int i = 1; i < this->packet.length; ++i)
		{
			temp[i - 1] = this->packet.bytes[i];
		}
		//free(this->packet.bytes);
		this->packet.bytes = std::move(temp);
		--this->packet.length;
	}

	return b;

}

void PacketHandler::write(byte b)
{
	this->writeByte(b);
}

void PacketHandler::write(const char* b)
{
	for(unsigned int i = 0; i < strlen(b); ++i)
	{
		this->writeByte(b[i]);
	}
}

void PacketHandler::write(byte* b, int len)
{
	for(int i = 0; i < len; ++i)
	{
		this->writeByte(b[i]);
	}
}

void PacketHandler::write(int b)
{
	this->writeByte((byte)(b & 0xFF));
	this->writeByte((byte)((b >> 8) & 0xFF));
	this->writeByte((byte)((b >> 16) & 0xFF));
	this->writeByte((byte)((b >> 24) & 0xFF));	
}

void PacketHandler::write(_short b)
{
	this->writeByte((byte)(b & 0xFF));
	this->writeByte((byte)((b >> 8) & 0xFF));
}

void PacketHandler::write(_double b)
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

void PacketHandler::write(std::string b)
{
	for(unsigned int i = 0; i < b.length(); ++i)
	{
		this->write((byte)b[i]);
	}
}

int PacketHandler::readInt()
{
	byte b1 = this->readByte();
	byte b2 = this->readByte();
	byte b3 = this->readByte();
	byte b4 = this->readByte();

	return (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
}

_short PacketHandler::readShort()
{
	byte b1 = this->readByte();
	byte b2 = this->readByte();

	return (b2 << 8) + b1;
}

_double PacketHandler::readDouble()
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

byte* PacketHandler::readString(int size)
{
	byte* bytes = (byte*)std::malloc(size);
	for(int i = 0; i < size; ++i)
	{
		bytes[i] = this->readByte();
	}
	return bytes;
}

byte* PacketHandler::nullTermBytes()
{
	byte* temp = (byte*) malloc(this->packet.length + 1);
	for(int i = 0; i < this->packet.length; ++i)
	{
		temp[i] = this->packet.bytes[i];
	}
	temp[this->packet.length] = '\0';

	return temp;
}

void PacketHandler::skip(int n)
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

byte* PacketHandler::seek(int n)
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
