#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

// Header files
#include "Coin.h"
#include "PriceHistory.h"
#include "Transaction.h"
#include "Wallet.h"
#include "Account.h"

using namespace std;

// =====================
// MARKET CLASS
// =====================
class Market
{
private:
    vector<Coin> coins;
    map<string, PriceHistory> histories;

public:
    Market()
    {
        coins.push_back(Coin("Bitcoin", "BTC", 50000.0));
        coins.push_back(Coin("Ethereum", "ETH", 4000.0));
        coins.push_back(Coin("Doge", "DOGE", 0.25));
        coins.push_back(Coin("Cardano", "ADA", 2.0));
        coins.push_back(Coin("Zcoin", "ZEE", 45000.0));
        coins.push_back(Coin("ABCoin", "AB", 45000.0));

        PriceHistory btc("BTC");
        btc.addPrice(2020, 29000);
        btc.addPrice(2021, 47000);
        btc.addPrice(2022, 16500);
        btc.addPrice(2023, 42000);
        btc.addPrice(2024, 93000);
        histories["BTC"] = btc;

        PriceHistory eth("ETH");
        eth.addPrice(2020, 730);
        eth.addPrice(2021, 3700);
        eth.addPrice(2022, 1200);
        eth.addPrice(2023, 2280);
        eth.addPrice(2024, 3400);
        histories["ETH"] = eth;

        PriceHistory doge("DOGE");
        doge.addPrice(2020, 0.004);
        doge.addPrice(2021, 0.17);
        doge.addPrice(2022, 0.07);
        doge.addPrice(2023, 0.09);
        doge.addPrice(2024, 0.38);
        histories["DOGE"] = doge;

        PriceHistory ada("ADA");
        ada.addPrice(2020, 0.18);
        ada.addPrice(2021, 1.30);
        ada.addPrice(2022, 0.26);
        ada.addPrice(2023, 0.60);
        ada.addPrice(2024, 0.90);
        histories["ADA"] = ada;

        PriceHistory zee("ZEE");
        zee.addPrice(2020, 12000);
        zee.addPrice(2021, 38000);
        zee.addPrice(2022, 21000);
        zee.addPrice(2023, 31000);
        zee.addPrice(2024, 45000);
        histories["ZEE"] = zee;

        PriceHistory ab("AB");
        ab.addPrice(2020, 8000);
        ab.addPrice(2021, 29000);
        ab.addPrice(2022, 15000);
        ab.addPrice(2023, 38000);
        ab.addPrice(2024, 45000);
        histories["AB"] = ab;
    }

    void displayMarket()
    {
        cout << "\n=== Market ===" << endl;
        for (int i = 0; i < coins.size(); i++)
        {
            cout << i + 1 << ". ";
            coins[i].displayInfo();
            cout << endl;
        }
    }

    Coin *getCoin(string symbol)
    {
        for (int i = 0; i < coins.size(); i++)
        {
            if (coins[i].getSymbol() == symbol)
                return &coins[i];
        }
        return nullptr;
    }

    void addCoin(Coin c) { coins.push_back(c); }

    void updateCoinPrice(string symbol, double newPrice)
    {
        for (int i = 0; i < coins.size(); i++)
        {
            if (coins[i].getSymbol() == symbol)
            {
                coins[i].setPrice(newPrice);
                cout << "Price updated successfully!" << endl;
            }
        }
    }

    void viewHistory(string symbol)
    {
        auto it = histories.find(symbol);
        if (it == histories.end())
        {
            cout << "No history found for " << symbol << endl;
            return;
        }
        it->second.displayHistory();
    }
};

// =====================
// PORTFOLIO CLASS
// =====================
class Portfolio
{
private:
    map<string, double> holdings;
    double totalValue;

public:
    Portfolio() : totalValue(0) {}

    void updateHoldings(map<string, double> h) { holdings = h; }

    void displayPortfolio(Market &market)
    {
        cout << "\n=== Portfolio ===" << endl;
        totalValue = 0;
        if (holdings.empty())
        {
            cout << "No coins in portfolio yet." << endl;
            return;
        }
        for (auto &h : holdings)
        {
            Coin *coin = market.getCoin(h.first);
            if (coin != nullptr)
            {
                double value = coin->getPrice() * h.second;
                totalValue += value;
                cout << h.first << ": " << h.second
                     << " coins = $" << value << endl;
            }
        }
        cout << "Total Portfolio Value: $" << totalValue << endl;
    }
};

// =====================
// USER CLASS
// Inherits from Account
// =====================
class User : public Account
{
private:
    Wallet wallet;
    Portfolio portfolio;
    vector<Transaction> transactionHistory;
    string transactionFile; // each user has their own transaction file

public:
    User() : Account("", ""), wallet(0), transactionFile("") {}

    User(string u, string p, double balance)
        : Account(u, p), wallet(balance)
    {
        transactionFile = u + "_transactions.txt";
    }

    void buy(Market &market, string symbol, double qty)
    {
        Coin *coin = market.getCoin(symbol);
        if (coin == nullptr)
        {
            cout << "Coin not found!" << endl;
            return;
        }
        double totalCost = coin->getPrice() * qty;
        if (wallet.withdraw(totalCost))
        {
            wallet.addCoin(symbol, qty);
            Transaction t("BUY", symbol, qty, coin->getPrice(), "2025-01-01");
            t.saveToFile(transactionFile);
            transactionHistory.push_back(t);
            cout << "Purchase successful! Spent $" << totalCost << endl;
        }
    }

    void sell(Market &market, string symbol, double qty)
    {
        Coin *coin = market.getCoin(symbol);
        if (coin == nullptr)
        {
            cout << "Coin not found!" << endl;
            return;
        }
        if (wallet.removeCoin(symbol, qty))
        {
            double totalValue = coin->getPrice() * qty;
            wallet.deposit(totalValue);
            Transaction t("SELL", symbol, qty, coin->getPrice(), "2025-01-01");
            t.saveToFile(transactionFile);
            transactionHistory.push_back(t);
            cout << "Sale successful! Received $" << totalValue << endl;
        }
    }

    void viewWallet() { wallet.displayWallet(); }

    void viewPortfolio(Market &market)
    {
        portfolio.updateHoldings(wallet.getHoldings());
        portfolio.displayPortfolio(market);
    }

    void viewHistory() { Transaction::loadFromFile(transactionFile); }
};

// =====================
// ADMIN CLASS
// Inherits from Account
// =====================
class Admin : public Account
{
private:
    string adminCode;

public:
    Admin(string u, string p, string code)
        : Account(u, p), adminCode(code) {}

    void addCoin(Market &market, string name, string symbol, double price)
    {
        market.addCoin(Coin(name, symbol, price));
        cout << "Coin added successfully!" << endl;
    }

    void updatePrice(Market &market, string symbol, double newPrice)
    {
        market.updateCoinPrice(symbol, newPrice);
    }

    void displayAdminMenu()
    {
        cout << "\n=== Admin Panel ===" << endl;
        cout << "1. Add New Coin" << endl;
        cout << "2. Update Coin Price" << endl;
        cout << "3. Exit Admin Panel" << endl;
        cout << "Enter choice: ";
    }
};

// =====================
// TRADE MANAGER CLASS
// =====================
class TradeManager
{
private:
    int totalTrades;
    int totalBuys;
    int totalSells;

public:
    TradeManager() : totalTrades(0), totalBuys(0), totalSells(0) {}

    void recordBuy()
    {
        totalTrades++;
        totalBuys++;
    }
    void recordSell()
    {
        totalTrades++;
        totalSells++;
    }

    void displayStats()
    {
        cout << "\n=== Trade Statistics ===" << endl;
        cout << "Total Trades: " << totalTrades << endl;
        cout << "Total Buys:   " << totalBuys << endl;
        cout << "Total Sells:  " << totalSells << endl;
    }
};

// =====================
// EXCHANGE CLASS
// =====================
class Exchange
{
private:
    Market market;
    Admin admin;
    TradeManager tradeManager;
    vector<User> users;

public:
    Exchange() : admin("admin", "admin123", "admincode") {}

    void registerUser()
    {
        string username, password;
        double balance;
        cout << "\n=== Register New Account ===" << endl;
        cout << "Enter username: ";
        cin >> username;

        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == username)
            {
                cout << "Username already taken!" << endl;
                return;
            }
        }

        cout << "Enter password: ";
        cin >> password;
        cout << "Enter starting balance: $";
        cin >> balance;

        users.push_back(User(username, password, balance));
        cout << "Account created! Welcome, " << username << "!" << endl;
    }

    void loginUser()
    {
        if (users.empty())
        {
            cout << "No accounts registered yet! Please register first." << endl;
            return;
        }

        string username, password;
        cout << "\n=== User Login ===" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        int foundIndex = -1;
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].login(username, password))
            {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == -1)
        {
            cout << "Invalid username or password!" << endl;
            return;
        }

        cout << "\nWelcome back, " << users[foundIndex].getUsername() << "!" << endl;

        int choice;
        do
        {
            cout << "\n=== CryptoSim Menu ===" << endl;
            cout << "1. View Market" << endl;
            cout << "2. Buy Coin" << endl;
            cout << "3. Sell Coin" << endl;
            cout << "4. View Wallet" << endl;
            cout << "5. View Portfolio" << endl;
            cout << "6. View Transaction History" << endl;
            cout << "7. View Price History" << endl;
            cout << "8. Logout" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1)
            {
                market.displayMarket();
            }
            else if (choice == 2)
            {
                string symbol;
                double qty;
                market.displayMarket();
                cout << "Enter coin symbol: ";
                cin >> symbol;
                cout << "Enter quantity: ";
                cin >> qty;
                users[foundIndex].buy(market, symbol, qty);
                tradeManager.recordBuy();
            }
            else if (choice == 3)
            {
                string symbol;
                double qty;
                cout << "Enter coin symbol: ";
                cin >> symbol;
                cout << "Enter quantity: ";
                cin >> qty;
                users[foundIndex].sell(market, symbol, qty);
                tradeManager.recordSell();
            }
            else if (choice == 4)
            {
                users[foundIndex].viewWallet();
            }
            else if (choice == 5)
            {
                users[foundIndex].viewPortfolio(market);
            }
            else if (choice == 6)
            {
                users[foundIndex].viewHistory();
            }
            else if (choice == 7)
            {
                string sym;
                cout << "Enter coin symbol (BTC/ETH/DOGE/ADA/ZEE/AB): ";
                cin >> sym;
                market.viewHistory(sym);
            }
            else if (choice == 8)
            {
                cout << "Logged out successfully!" << endl;
            }
            else
            {
                cout << "Invalid choice!" << endl;
            }
        } while (choice != 8);
    }

    void loginAdmin()
    {
        string username, password;
        cout << "\n=== Admin Login ===" << endl;
        cout << "Enter admin username: ";
        cin >> username;
        cout << "Enter admin password: ";
        cin >> password;

        if (!admin.login(username, password))
        {
            cout << "Invalid admin credentials!" << endl;
            return;
        }

        cout << "Admin access granted!" << endl;

        int choice;
        do
        {
            admin.displayAdminMenu();
            cin >> choice;

            if (choice == 1)
            {
                string name, symbol;
                double price;
                cout << "Enter coin name: ";
                cin >> name;
                cout << "Enter coin symbol: ";
                cin >> symbol;
                cout << "Enter coin price: $";
                cin >> price;
                admin.addCoin(market, name, symbol, price);
            }
            else if (choice == 2)
            {
                string symbol;
                double price;
                cout << "Enter coin symbol: ";
                cin >> symbol;
                cout << "Enter new price: $";
                cin >> price;
                admin.updatePrice(market, symbol, price);
            }
            else if (choice == 3)
            {
                cout << "Exiting admin panel." << endl;
            }
            else
            {
                cout << "Invalid choice!" << endl;
            }
        } while (choice != 3);
    }

    void start()
    {
        int choice;
        do
        {
            cout << "\n=== Welcome to CryptoSim ===" << endl;
            cout << "1. Register New Account" << endl;
            cout << "2. Login as User" << endl;
            cout << "3. Login as Admin" << endl;
            cout << "4. View Trade Statistics" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1)
                registerUser();
            else if (choice == 2)
                loginUser();
            else if (choice == 3)
                loginAdmin();
            else if (choice == 4)
                tradeManager.displayStats();
            else if (choice == 5)
                cout << "Thank you for using CryptoSim. Goodbye!" << endl;
            else
                cout << "Invalid choice!" << endl;

        } while (choice != 5);
    }
};

// =====================
// MAIN
// =====================
int main()
{
    Exchange ex;
    ex.start();
    return 0;
}