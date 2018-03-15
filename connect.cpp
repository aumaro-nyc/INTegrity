/* Source: https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html */

#include <stdlib.h>
#include <iostream>
#include "cppconn/include/mysql_connection.h"
#include "cppconn/include/cppconn/driver.h"
#include "cppconn/include/cppconn/exception.h"
#include "cppconn/include/cppconn/resultset.h"
#include "cppconn/include/cppconn/statement.h"

using namespace std;

int main(void) {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    
    // Create connection
    driver = get_driver_instance();
    con = driver->connect("ix-dev.cs.uoregon.edu", "mfreder", "Enjolras13");
    
    // Connect to MySQL database
    con->setSchema("Data");
}
