#ifndef PACKET_H
#define PACKET_H

#include <memory>
#include <vector>
#include <string>

using byte = unsigned char;
using _short = unsigned short int;
using _double = unsigned long long int;


class Packet
{
	public:
		Packet();
		Packet(std::string bytes);
		Packet(std::vector<byte> bytes, int length);
		~Packet();
	
		void setBytes(std::vector<byte> bytes, int length);

		int length;
		std::vector<byte> bytes;
};

#endif
