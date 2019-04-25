#include "tools/packets/PacketStream.h"

int main(int argc, char* argv[])
{

//	std::cout << BOOST_VERSION /100000 << "." << BOOST_VERSION / 100 % 1000 << "." << BOOST_VERSION % 100 << '\n';







	PacketStream handler = PacketStream();
	handler.write("bro");
	std::cout << handler.readString(3) << '\n';

	_double d = 234234234234;
	handler.write(d);

//	std::cout << (handler.getByteStreamHex()).str().c_str() << '\n';



/*
	Packet p = Packet();
	_double d = 2524233452452315;
	_short s = 2;
	std::string t = "hello";

	byte temp = 0x41;
	p.write(temp);

	p.write(s);
	p.write(d);

	std::cout << p.readDouble() << '\n';
	std::cout << p.getRawBytes() << '\n';

	std::ostringstream str = p.getByteStream();
	std::cout << str.str().c_str() << '\n';
	
	str = p.getByteStreamHex();
	std::cout << str.str().c_str() << '\n';

	std::string ts = str.str();
	std::cout << ts << '\n';

	std::cout << std::hex << (int)p.readByte() << std::dec << '\n';

	//const char* temp2 = ts.c_str();

	return 0;
*/
}
