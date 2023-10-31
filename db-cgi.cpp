/*
 * This program shows how to use the MySQL++ wrapper for the MySQL C APIs.
 * It connects a CGI program to a MySQL database.
 * This C++ program works with the registration page. Once the user enters their information in all the
 * text box fields and clicks submit, the data is stored in the MySQL database for future login use and
 * the user is redirected to the main page with options.
 * Author: Malak Lamsettef
 */

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
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

    map<string, string> Get;
    initializePost(Get);
    cout << "Content-type: text/html" << endl
         << endl;
    cout << "<html><body>" << endl;
    cout << "<h2>Registration Form processed. Here is what we got</h2>" << endl;

    std::string username;
    std::string password;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string street;
    std::string city;
    std::string state;
    std::string zip;
    std::string country;

    user *userObject = new user(username);
    // Retrieves all the following information from the user
    if (Get.find("username") != Get.end() && Get.find("password") != Get.end() &&
        Get.find("firstName") != Get.end() && Get.find("lastName") != Get.end() &&
        Get.find("email") != Get.end() && Get.find("street") != Get.end() &&
        Get.find("city") != Get.end() && Get.find("state") != Get.end() && Get.find("zip") != Get.end() && Get.find("country") != Get.end())
    {
        cout << "<p>You entered, username: " << Get["username"] << " and password: " << Get["password"] << endl;
        username = Get["username"];

        userObject->username = username;

        password = Get["password"];
        firstName = Get["firstName"];
        lastName = Get["lastName"];
        email = Get["email"];
        street = Get["street"];
        city = Get["city"];
        state = Get["state"];
        zip = Get["zip"];
        country = Get["country"];
        // Else, tell the user to fill out the form and press submit in order for them to
        // be directed to the page with options
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

        query << "INSERT into lamsetmUsers (username, password, firstName, lastName, email, street, city, state, zip, country) VALUES('" + username + "','" + password + "','" + firstName + "','" + lastName + "','" + email >

            query.parse(); // check to ensure it is correct

        // Run the query
        mysqlpp::SimpleResult result = query.execute();

        // If the statement is true, print out registration was a success and direct the user to
        // the main page with the options
        if (result)
        {
            cout << "<p>Registration was a success. Welcome!\n";
            cout << "<p>Please take 3 seconds to review login info\n";
            cout << "<meta http-equiv='refresh' content = '3; url = options.html'>";
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
