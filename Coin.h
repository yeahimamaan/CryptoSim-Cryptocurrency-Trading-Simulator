#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <string>
using namespace std;

class Coin
{
private:
    string name;
    string symbol;
    double price;

public:
    Coin() : name(""), symbol(""), price(0.0) {}
    Coin(string n, string s, double p) : name(n), symbol(s), price(p) {}

    void displayInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Symbol: " << symbol << endl;
        cout << "Price: $" << price << endl;
    }

    string getName() const { return name; }
    string getSymbol() const { return symbol; }
    double getPrice() const { return price; }
    void setPrice(double p) { price = p; }
};

#endif