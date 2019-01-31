#ifndef PacketHandler_H
#define PacketHandler_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <string.h>

#include "Packet.h"
/* Included from Packet.h
 *
 * memory
 *
 */

class PacketHandler
{
    public:
	PacketHandler();
	~PacketHandler();

	Packet* getPacket();

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
	byte* readString(int size);

    private:
	Packet packet;
	int header;
};

#endif
