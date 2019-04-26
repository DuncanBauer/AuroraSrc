#include <string>
#include <map>


class ConfigParser
{
	public:
		std::map<std::string, std::string> getValuesFromFile(std::string filename);

	private:
		ConfigParser();
};
