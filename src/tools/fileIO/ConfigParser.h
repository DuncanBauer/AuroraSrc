#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include <map>


namespace ConfigParser
{
	std::map<std::string, std::string> getValuesFromFile(std::string filename);
};

#endif
