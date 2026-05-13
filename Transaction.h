#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Transaction
{
private:
    string type;
    string coinName;
    double quantity;
    double priceAtTime;
    string timestamp;

public:
    Transaction(string t, string c, double q, double p, string ts)
        : type(t), coinName(c), quantity(q), priceAtTime(p), timestamp(ts) {}

    void displayTransaction()
    {
        cout << "Type: " << type << endl;
        cout << "Coin: " << coinName << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Price at Time: $" << priceAtTime << endl;
        cout << "Timestamp: " << timestamp << endl;
    }

    // Saves transaction to users own file
    void saveToFile(string filename)
    {
        ofstream file(filename, ios::app);
        file << type << "," << coinName << "," << quantity << ","
             << priceAtTime << "," << timestamp << endl;
        file.close();
    }

    // Loads and displays all transactions from users file
    static void loadFromFile(string filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "No transaction history found." << endl;
            return;
        }
        string line;
        cout << "=== Transaction History ===" << endl;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }

    string getType() const { return type; }
    string getCoinName() const { return coinName; }
    double getQuantity() const { return quantity; }
    double getPriceAtTime() const { return priceAtTime; }
    string getTimestamp() const { return timestamp; }
};

#endif