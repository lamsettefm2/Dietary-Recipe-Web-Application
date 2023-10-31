/*
 * This program shows how to use the MySQL++ wrapper for the MySQL C APIs.
 * It connects a CGI program to a MySQL database.
 * This C++ program works with the login page. If the username and password the user enters
 * is in the MySQL database the login is successful and they are redirected to main page with options.
 * Else, login fails and they are redirected to main welcome page.
 * Author: Malak Lamsettef
 */

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include "getpost.h"
#include "class.h"

using namespace std;

int main(int argc, char *argv[])
{

    map<string, string> Get;
    initializePost(Get);
    cout << "Content-type: text/html" << endl
         << endl;
    cout << "<html><body>" << endl;
    cout << "<h2>Login Form Page</h2>" << endl;

    std::string password;

    // Retrieves the username and password the user enters
    if (Get.find("username") != Get.end() && Get.find("password") != Get.end())
    {
        username = Get["username"];
        password = Get["password"];
    }
    else
    {
        cout << "<p>Fill out the form and press submit" << endl;
    }
    cout << "</body></html>" << endl;

    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false); // Exceptions suppressed to keep code simple
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {

        // Create a query
        mysqlpp::Query query = conn.query();

        query << "SELECT * from lamsetmUsers where username = %0q and password = %1q;";

        query.parse(); // check to ensure it is correct

        // Run the query -- note INSERT does not return results so we are using SimpleResult
        mysqlpp::StoreQueryResult result = query.store(username, password);

        // Always check for errors
        // If the statement is true, print out login was successful and redirect user to page with options
        if (result.num_rows() > 0)
        {
            cout << "<p>Login was Successful\n";
            cout << "<p>Please wait 3 seconds to be directed to the main page.\n";
            cout << "<meta http-equiv='refresh' content = '3; url = options.html'>";
            // Else, if the statement is false, login fails and redirects user to main welcome page
        }
        else
        {
            cout << "Login failed, wait 3 seconds to redirect to main welcome page: " << endl;
            cout << "<meta http-equiv='refresh' content = '3; url = form2.html'>";
        }
        return (0);
    }
    else
    {
        cerr << "Connection failed: " << conn.error() << endl;
        return (1);
    }
}