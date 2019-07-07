#include "MySQLConn.h"


#include "../../tools/ConfigParser.h"
#include <iostream>

#include <cstdio>
#include <string.h>

MySQLConn::MySQLConn()
{
	std::cout << "MYSQL STARTED" << '\n';
   
	std::map<std::string, std::string> config = ConfigParser::getValuesFromFile("db.conf");
	this->host = config["host"];
	this->port = std::stoi(config["port"]);
	this->user = config["user"];
	this->pass = config["pass"];
	this->schema = config["schema"];

	std::string location = "tcp://" + this->host + ":" + std::to_string(this->port);

	try
	{
		this->driver = get_driver_instance();
		this->con = this->driver->connect(location, this->user, this->pass);
		this->con->setSchema(this->schema);
   
		sql::Statement * stmt;
		stmt = con->createStatement();
		sql::ResultSet * res;
		res = stmt->executeQuery("SELECT * FROM accounts");
		while(res->next())
		{
			std::cout << res->getString(2) << '\n';
		}

		delete res;
		delete stmt;
	}
	catch(sql::SQLException &e) 
	{
		std::cout << "SQL Exception" << '\n';
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << '\n';
	}
}

MySQLConn::~MySQLConn()
{
	delete con;
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
