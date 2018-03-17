/*
 * Author: Meg Fredericks   
 * File: connect.h
 */

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include "cppconn/include/mysql_connection.h"
#include "cppconn/include/driver.h"
#include "cppconn/include/exception.h"
#include "cppconn/include/resultset.h"
#include "cppconn/include/statement.h"
#include "cppconn/include/prepared_statement.h"

using namespace std;

class Connect {
public:
    sql::Driver *driver;
    sql::Connection *con;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
    Connect(string);
    virtual ~Connect();
    int executeQuery(string);
};

#endif
