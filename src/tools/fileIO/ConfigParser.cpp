#include "ConfigParser.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

ConfigParser::ConfigParser()
{
}

ConfigParser::~ConfigParser()
{
}

std::map<std::string, std::string> ConfigParser::getValuesFromFile(std::string filename)
{
	std::map<std::string, std::string> config;
	
	char cwd[PATH_MAX];
	if(getcwd(cwd, sizeof(cwd)) == NULL)
	{
		std::cout << "Couldn't get path" << '\n';
	}


	std::string line;
	std::ifstream file;
	file.open(filename);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			if(line.front() == '#' || line.length() <= 1)
			{
				continue;
			}
			else
			{
				std::string key = line.substr(0, line.find('='));
				std::string value = line.substr(line.find('=')+1, line.size()-1);
				config.emplace(key, value);
				std::cout << key << ": " << value << '\n';
			}
		}
	}
	file.close();

	return config;
}
