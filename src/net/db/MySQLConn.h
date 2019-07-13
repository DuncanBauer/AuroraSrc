#ifndef MYSQLCONN_H
#define MYSQLCONN_H

#if defined(__linux__)
	#warning "Linux"
	#include "mysql_connection.h"
//	#include "mysqlcppconn8/mysqlx/xdevapi.h"
	#include "cppconn/driver.h"
	#include "cppconn/exception.h"
	#include "cppconn/resultset.h"
	#include "cppconn/statement.h"
#else
	#warning "OTHER"
	#include "mysqlcppconn8/mysqlx/xdevapi.h"
//	#include "mysqlcppconn8/jdbc/mysql_connection.h"
//	#include "mysqlcppconn8/jdbc/cppconn/driver.h"
//	#include "mysqlcppconn8/jdbc/cppconn/exception.h"
//	#include "mysqlcppconn8/jdbc/cppconn/resultset.h"
//	#include "mysqlcppconn8/jdbc/cppconn/statement.h"
#endif

#include <string>


class MySQLConn
{
	public:
		MySQLConn();
		~MySQLConn();

		bool connect();
		bool disconnect();
		bool query();

	private:
		std::string host;
		int port;
		std::string user;
		std::string pass;
		std::string schema;

        // LEGACY VARIABLES FOR LINUX SINCE I CANT INSTALL MYSQL CONNECTOR 8 ON ANY OF MY MACHINES
		//sql::Connection *con;
		//sql::Driver *driver;
};


#endif
