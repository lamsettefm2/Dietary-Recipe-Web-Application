/*
 * This program shows how to use the MySQL++ wrapper for the MySQL C APIs.
 * It connects a CGI program to a MySQL database.
 * This C++ program works with the comments page. Once the user enters their information and message
 * in the comment section page and clicks submit, the data is stored in the
 * MySQL database and prints out in the blog
 * Author: Malak Lamsettef
 */

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include <fstream>
#include "getpost.h"

using namespace std;

class user
{
public:
    user(string username)
    {
        username = username;
    }
    string username;
};

int main(int argc, char *argv[])
{
    cout << "Content-type: text/html" << endl
         << endl;
    cout << "<html><body>" << endl;
    // Display navigation bar that links to the other webpages
    cout << "<nav class='navbar'>\n<a href='options.html'>Home</a>\n
        <a href = 'options.cgi' > Blog</ a>\n<a href = 'index.cgi'> All Recipes</ a>\n<a href = 'comments.html'> Comment</ a>\n
        <a href = 'add.html'> Add Your Recipe</ a>\n</ nav> " << endl;
    cout << "<h2>All Comments</h2>" << endl;

    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false); // Exceptions suppressed to keep code simple
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {

        // Create a query
        mysqlpp::Query query = conn.query();

        query << "SELECT * FROM lamsetmComments;";

        query.parse(); // check to ensure it is correct

        // Run the query
        mysqlpp::StoreQueryResult result = query.store();

        // Always check for errors
        if (result)
        {
            for (int i = 0; i < result.num_rows(); ++i)
            {
                // Print out name, title, and comment
                cout << "<a>"
                     << "<li>" << result[i]["name"] << ",'" << result[i]["title"]
                     << "' : " << result[i]["comment"] << "</a></li>" << endl;

                cout << "</li>" << endl;
            }
            cout << "</body></html>" << endl;
        }
        else
        {
            cerr << "Query error: " << query.error() << endl;
        }
        return (0);
    }
    else
    {
        cerr << "Connection failed: " << conn.error() << endl;
        return (1);
    }
}
