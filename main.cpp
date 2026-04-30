#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Coin
{
private:
    string name;
    string symbol;
    double price;

public:
    Coin(string n, string s, double p) : name(n), symbol(s), price(p) {}

    void displayInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Symbol: " << symbol << endl;
        cout << "Price: $" << price << endl;
    }
};

class Transaction
{
private:
    string type;
    string CoinName;
    double quantity;
    double priceAtTime;
    string timestamp;

public:
    Transaction(string t, string c, double q, double p, string ts) : type(t), CoinName(c), quantity(q), priceAtTime(p), timestamp(ts) {}

    void displayTransaction()
    {
        cout << "Type: " << type << endl;
        cout << "Coin: " << CoinName << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Price at Time: $" << priceAtTime << endl;
        cout << "Timestamp: " << timestamp << endl;
    }
};

class Wallet
{
private:
    double usdtBalance;
    map<string, double> holdings; // Coin name and quantity

public:
    Wallet(double balance) : usdtBalance(balance) {}
};

class Market
{
private:
    vector<Coin> coins;

public:
    Market()
    {
        coins.push_back(Coin("Bitcoin", "BTC", 50000.0));
        coins.push_back(Coin("Ethereum", "ETH", 4000.0));
        coins.push_back(Coin("Doge", "DOGE", 0.25));
        coins.push_back(Coin("Cardano", "ADA", 2.0));
        coins.push_back(Coin("Zcoin", "ZEE", 45000));
    }
};
