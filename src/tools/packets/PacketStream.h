#ifndef PacketStream_H
#define PacketStream_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include <string.h>

#include "Packet.h"
/* Included from Packet.h
 *
 * memory
 *
 */

class PacketStream
{
    public:
	PacketStream();
	~PacketStream();

	Packet getPacket();
	void setPacket(Packet packet);

	std::ostringstream getByteStream();
	std::ostringstream getByteStreamHex();

	void writeByte(byte b);
	byte readByte();
	void write(byte b);
	void write(const char *b);
	void write(byte* b, int len);
	void write(int b);
	void write(_short b);
	void write(_double b);
	void write(std::string b);
	
	int readInt();
	_short readShort();
	_double readDouble();
	std::string readString(int size);

	void nullTermBytes(byte * arr);

	void skip(int n);
	void seek(int n, byte * arr);

    private:
	Packet packet;
	int header;
};

#endif
