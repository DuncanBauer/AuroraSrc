#include "ConfigParser.h"
#include <iostream>

ConfigParser::ConfigParser()
{
}

std::map<std::string, std::string> ConfigParser::getValuesFromFile(std::string filename)
{
	std::cout << "Called statically\n";
	std::cout << filename << '\n';
}
