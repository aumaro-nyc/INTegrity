/* 
 * Author: Meg Fredericks
 * File: connect.cpp
 *
 * connects to mySQL database
 *
 * Adapted from: https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html 
 */

#include "connect.h"

using namespace std;

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

int main(void) {
    return 0;
}
