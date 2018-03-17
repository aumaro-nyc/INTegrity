/* 
 * Author: Meg Fredericks
 * File: connect.cpp
 *
 * connects to mySQL database
 *
 * Adapted from: https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html 
 */

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
        //sql::Statement *stmt;
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;
        Connect(string);
        virtual ~Connect();
        int executeQuery(string);
};

Connect::Connect(string schema) {
    driver = get_driver_instance();
    con = driver->connect("ix-dev.cs.uoregon.edu:3118", "mfreder", "Enjolras13");
    cout << "Successfully connected to server.\n";
    con->setSchema(schema);
    cout << "Schema set to " << schema << ".\n";
}

int Connect::executeQuery(string query) {
    sql::Statement *stmt;
    stmt = con->createStatement();
    stmt->execute(query);
    delete stmt;
    return 1;
}

Connect::~Connect() {
    delete con;
    cout << "Connection deleted.\n";
}

/*int main(void) {
    try {
        // Declare variables
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
        string test = "INSERT INTO Person(email, pw, pub_key, priv_key) VALUES(\"test@test.com\", \"password\", \"123\", \"456\")";
        Connect c = Connect("Data");
        c.executeQuery(test);
        
        // Prepared statement test
        pstmt = con->prepareStatement("SELECT email FROM Person;");
        res = pstmt->executeQuery();
        delete pstmt;
        
        // Free variables
        delete con;
        return 0;
        
    } catch (sql::SQLException &e) {
        cout << "SQLException\n";
        return 0;
    }
} */
