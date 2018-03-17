/* Source: https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html */

#include <cstdlib>
#include <iostream>
#include "cppconn/include/mysql_connection.h"
#include "cppconn/include/driver.h"
#include "cppconn/include/exception.h"
#include "cppconn/include/resultset.h"
#include "cppconn/include/statement.h"
#include "cppconn/include/prepared_statement.h"

using namespace std;

int main(void) {
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        cout << "variables set\n";
 
        // Create connection
        driver = get_driver_instance();
        cout << "got instance\n";
        con = driver->connect("ix-dev.cs.uoregon.edu:3118", "mfreder", "Enjolras13");
    	cout << "connected to server\n";
        
        // Connect to MySQL database
        con->setSchema("Data");
        
        // Statement test
        stmt = con->createStatement();
        stmt->execute("INSERT INTO Person(email, pw, pub_key, priv_key) VALUES(\"test@test.com\", \"password\", \"123\", \"456\")");
        delete stmt;
        
        // Prepared statement test
        pstmt = con->prepareStatement("SELECT email FROM Person;");
        res = pstmt->executeQuery();
        delete pstmt;
        
        // Free variables
        delete con;
        
    } catch (sql::SQLException &e) {
        cout << "SQLException\n";
    }
}
