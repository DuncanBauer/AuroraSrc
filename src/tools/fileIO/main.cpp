#include "ConfigParser.h"

int main()
{
	ConfigParser parser = ConfigParser();
	std::map<std::string, std::string> config = parser.getValuesFromFile("master.conf");

	return 0;
}
