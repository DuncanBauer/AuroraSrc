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
	std::cout << "Called statically\n";
	std::cout << filename << '\n';
	std::map<std::string, std::string> config;
	
	char cwd[PATH_MAX];
	if(getcwd(cwd, sizeof(cwd)) != NULL)
	{
		std::cout << "CWD: " << cwd << '\n';
	}


	std::string line;
	std::ifstream file;
	file.open(filename);
	if(file.is_open())
	{
		std::cout << "open\n";
		while(getline(file, line))
		{
			std::cout << line << '\n';
		}
	}
	file.close();

	return config;
}
