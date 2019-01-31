#ifndef PACKET_H
#define PACKET_H

#include <memory>

using byte = unsigned char;
using _short = unsigned short int;
using _double = unsigned long long int;

class Packet
{
	public:
		Packet();
		Packet(byte* bytes, int length);
		~Packet();
	
		void setBytes(byte* bytes, int length);

		int length = 0;
		byte* bytes = nullptr;
};

#endif
