/* Source: https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html */

#include <cstdlib>
#include <iostream>
#include "cppconn/include/mysql_connection.h"
#include "cppconn/include/driver.h"
#include "cppconn/include/exception.h"
#include "cppconn/include/resultset.h"
#include "cppconn/include/statement.h"

using namespace std;

int main(void) {
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
    
        // Create connection
        //driver = get_driver_instance();
        con = driver->connect("ix-dev.cs.uoregon.edu", "mfreder", "Enjolras13");
    
        // Connect to MySQL database
        con->setSchema("Data");
    } catch (sql::SQLException &e) {
        cout << "SQLException\n";
    }
}
