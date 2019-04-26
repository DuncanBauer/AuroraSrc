#include <string>
#include <map>


class ConfigParser
{
	public:
		ConfigParser();
		~ConfigParser();
		static std::map<std::string, std::string> getValuesFromFile(std::string filename);

	private:
};
