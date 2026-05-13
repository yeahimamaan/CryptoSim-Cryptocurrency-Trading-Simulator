#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <string>
#include <map>
using namespace std;

class Wallet
{
private:
    double usdtBalance;
    map<string, double> holdings; // symbol -> quantity

public:
    Wallet() : usdtBalance(0.0) {}
    Wallet(double balance) : usdtBalance(balance) {}

    void deposit(double amount)
    {
        usdtBalance += amount;
    }

    bool withdraw(double amount)
    {
        if (amount > usdtBalance)
        {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        usdtBalance -= amount;
        return true;
    }

    void addCoin(string symbol, double qty)
    {
        holdings[symbol] += qty;
    }

    bool removeCoin(string symbol, double qty)
    {
        if (holdings[symbol] < qty)
        {
            cout << "Insufficient coins!" << endl;
            return false;
        }
        holdings[symbol] -= qty;
        return true;
    }

    void displayWallet()
    {
        cout << "=== Wallet ===" << endl;
        cout << "USD Balance: $" << usdtBalance << endl;
        cout << "Holdings:" << endl;
        if (holdings.empty())
        {
            cout << "No coins owned yet." << endl;
        }
        for (auto &h : holdings)
        {
            cout << h.first << ": " << h.second << " coins" << endl;
        }
    }

    double getBalance() const { return usdtBalance; }
    map<string, double> getHoldings() const { return holdings; }
};

#endif