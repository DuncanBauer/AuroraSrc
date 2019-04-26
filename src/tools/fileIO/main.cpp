#include "ConfigParser.h"
#include <iostream>

int main()
{
	ConfigParser parser = ConfigParser();
	std::map<std::string, std::string> config = parser.getValuesFromFile("master.conf");


	for(auto const value: config)
	{
		std::cout << value.first << ": " << value.second << '\n';
	}
	
	return 0;
}
