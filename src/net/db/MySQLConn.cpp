#include "MySQLConn.h"


#include "../../tools/ConfigParser.h"


MySQLConn::MySQLConn()
{
	std::map<std::string, std::string> config = ConfigParser::getValuesFromFile("db.conf");
	this->host = config["host"];
	this->port = std::stoi(config["port"]);
	this->user = config["user"];
	this->pass = config["pass"];
	this->schema = config["schema"];

	std::string location = "tcp://" + this->host + ":" + std::to_string(this->port);
	this->driver = get_driver_instance();
	this->con = this->driver->connect(location, this->user, this->pass);
	this->con->setSchema(this->schema);

}

MySQLConn::~MySQLConn()
{
}

bool MySQLConn::connect()
{
}

bool MySQLConn::disconnect()
{
}

bool MySQLConn::query()
{
}
