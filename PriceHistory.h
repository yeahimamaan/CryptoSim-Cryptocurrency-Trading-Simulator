#ifndef PRICEHISTORY_H
#define PRICEHISTORY_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PriceHistory
{
private:
    string coinSymbol;
    vector<pair<int, double>> prices; // year, price

public:
    PriceHistory() : coinSymbol("") {}
    PriceHistory(string symbol) : coinSymbol(symbol) {}

    void addPrice(int year, double price)
    {
        prices.push_back({year, price});
    }

    void displayHistory()
    {
        if (prices.empty())
        {
            cout << "No history available." << endl;
            return;
        }
        cout << "=== Price History for " << coinSymbol << " ===" << endl;
        for (auto &p : prices)
            cout << p.first << ": $" << p.second << endl;
        cout << "Highest: $" << getHighest() << endl;
        cout << "Lowest:  $" << getLowest() << endl;
    }

    double getHighest()
    {
        double h = prices[0].second;
        for (auto &p : prices)
            if (p.second > h)
                h = p.second;
        return h;
    }

    double getLowest()
    {
        double l = prices[0].second;
        for (auto &p : prices)
            if (p.second < l)
                l = p.second;
        return l;
    }

    string getSymbol() const { return coinSymbol; }
};

#endif