#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

class Account
{
protected:
    string username;
    string password;

public:
    Account() : username(""), password("") {}
    Account(string u, string p) : username(u), password(p) {}

    // Returns true if credentials match
    bool login(string u, string p)
    {
        return (username == u && password == p);
    }

    string getUsername() const { return username; }
};

#endif