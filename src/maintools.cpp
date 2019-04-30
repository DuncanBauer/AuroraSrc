#include "tools/PacketStream.h"
#include "net/crypto/MapleAESOFB.h"

#if defined(_WIN32)
	#warning "WIN32"
	#include "../includes/mysqlcppconn8/jdbc/cppconn/driver.h"
	#include "../includes/boost/version.hpp"
#elif defined(_WIN64)
	#warning "WIN64"
	#include "../includes/mysqlcppconn8/jdbc/cppconn/driver.h"
	#include "../includes/boost/version.hpp"
#elif defined(__CYGWIN__)
	#warning "CYGWIN"
	#include "../includes/mysqlcppconn8/jdbc/cppconn/driver.h"
	#include "../includes/boost/version.hpp"
#elif defined(__linux__)
	#warning "Linux"
	#include "cppconn/driver.h"
	#include <boost/version.hpp>
#endif

int main(int argc, char* argv[])
{

	std::cout << BOOST_VERSION /100000 << "." << BOOST_VERSION / 100 % 1000 << "." << BOOST_VERSION % 100 << '\n';
	
	
	sql::Driver* driver;
	
	byte key[32] = {0x13, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, (byte) 0xB4, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00};
	byte ivRecv[4] = {70, 114, 122, 82};
	byte ivSend[4] = {82, 48, 120, 115};
	ivRecv[3] = (byte)(rand() % 255);
	ivSend[3] = (byte)(rand() % 255);
	MapleAESOFB send = MapleAESOFB(key, ivSend, (_short)(0xFFFF - 62));
	MapleAESOFB recv = MapleAESOFB(key, ivRecv, 62);
	
	byte arr[4] = {0x12, 0x63, 0xD2, 0x4E};
	recv.setIv(arr);
	byte * test = recv.getIv();

	std::cout << "Arr: " << arr << '\n';
	std::cout << "Test: " << test << '\n';






/*
	PacketStream handler = PacketStream();
	handler.write("bro");
	std::cout << handler.readString(3) << '\n';

	_double d = 234234234234;
	handler.write(d);
*/
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
