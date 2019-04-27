#include "MaplePacketCreator.h"
#include <iostream>

Packet MaplePacketCreator::getHandshake()
{
	PacketStream handler = PacketStream();
				
	_short s = 0x0d;
	handler.write(s);
			
	s = 62;
	handler.write(s);
				
	s = 0;
	handler.write(s);
	handler.write(s);

	byte b1 = (byte)(rand() % 255);
	byte b2 = (byte)(rand() % 255);
	byte b3 = (byte)(rand() % 255);
	byte b4 = (byte)(rand() % 255);
	byte arr[3] = {b1,b2,b3};
	byte arr2[3] = {b3,b2,b1};
		
	handler.write(arr, 3);
	handler.write(arr2, 3);
			
	byte b = 8;
	handler.write(b);
	return handler.getPacket();
}
