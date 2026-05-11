#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

// =====================
// COIN CLASS
// =====================
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

// =====================
// PRICE HISTORY CLASS
// Moved above Market because Market depends on it
// =====================
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

// =====================
// TRANSACTION CLASS
// Handles saving and loading transaction history per user
// =====================
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

    // Saves transaction to a file named after the user
    void saveToFile(string filename)
    {
        ofstream file(filename, ios::app);
        file << type << "," << coinName << "," << quantity << ","
             << priceAtTime << "," << timestamp << endl;
        file.close();
    }

    // Loads and displays all transactions from the users file
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

// =====================
// WALLET CLASS
// =====================
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

// =====================
// MARKET CLASS
// Stores all coins and their price histories
// =====================
class Market
{
private:
    vector<Coin> coins;
    map<string, PriceHistory> histories; // symbol -> price history

public:
    Market()
    {
        // Initialize coins
        coins.push_back(Coin("Bitcoin", "BTC", 50000.0));
        coins.push_back(Coin("Ethereum", "ETH", 4000.0));
        coins.push_back(Coin("Doge", "DOGE", 0.25));
        coins.push_back(Coin("Cardano", "ADA", 2.0));
        coins.push_back(Coin("Zcoin", "ZEE", 45000.0));
        coins.push_back(Coin("ABCoin", "AB", 45000.0));

        // Initialize price histories for each coin
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

    // Returns pointer to coin by symbol, nullptr if not found
    Coin *getCoin(string symbol)
    {
        for (int i = 0; i < coins.size(); i++)
        {
            if (coins[i].getSymbol() == symbol)
                return &coins[i];
        }
        return nullptr;
    }

    void addCoin(Coin c)
    {
        coins.push_back(c);
    }

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
// Shows total value of all holdings at current prices
// =====================
class Portfolio
{
private:
    map<string, double> holdings;
    double totalValue;

public:
    Portfolio() : totalValue(0) {}

    void updateHoldings(map<string, double> h)
    {
        holdings = h;
    }

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
// ACCOUNT CLASS (Base class for User and Admin)
// =====================
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

// =====================
// USER CLASS
// Inherits from Account
// Each user has their own wallet, portfolio and transaction file
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
        // Transaction file is named after the user
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
            // Save transaction to this users own file
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
            // Save transaction to this users own file
            Transaction t("SELL", symbol, qty, coin->getPrice(), "2025-01-01");
            t.saveToFile(transactionFile);
            transactionHistory.push_back(t);
            cout << "Sale successful! Received $" << totalValue << endl;
        }
    }

    void viewWallet()
    {
        wallet.displayWallet();
    }

    void viewPortfolio(Market &market)
    {
        portfolio.updateHoldings(wallet.getHoldings());
        portfolio.displayPortfolio(market);
    }

    // Loads transaction history from this users own file
    void viewHistory()
    {
        Transaction::loadFromFile(transactionFile);
    }
};

// =====================
// ADMIN CLASS
// Inherits from Account
// Can add coins and update prices
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
// Handles and displays all trades across the system
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
// Main controller - manages all users, admin, market
// Handles registration, login and menus
// =====================
class Exchange
{
private:
    Market market;
    Admin admin;
    TradeManager tradeManager;
    vector<User> users; // stores all registered users

public:
    // Admin credentials are set here
    Exchange() : admin("admin", "admin123", "admincode") {}

    // Register a new user profile
    void registerUser()
    {
        string username, password;
        double balance;
        cout << "\n=== Register New Account ===" << endl;
        cout << "Enter username: ";
        cin >> username;

        // Check if username already exists
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
        cout << "Account created successfully! Welcome, " << username << "!" << endl;
    }

    // Login as existing user and show their menu
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

        // Search for matching user
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

        // User menu loop
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
                cout << "Enter coin symbol (BTC, ETH, DOGE, ADA, ZEE, AB): ";
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

    // Login as admin with password protection
    void loginAdmin()
    {
        string username, password;
        cout << "\n=== Admin Login ===" << endl;
        cout << "Enter admin username: ";
        cin >> username;
        cout << "Enter admin password: ";
        cin >> password;

        // Verify admin credentials
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

    // Main menu of the application
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
            {
                registerUser();
            }
            else if (choice == 2)
            {
                loginUser();
            }
            else if (choice == 3)
            {
                loginAdmin();
            }
            else if (choice == 4)
            {
                tradeManager.displayStats();
            }
            else if (choice == 5)
            {
                cout << "Thank you for using CryptoSim. Goodbye!" << endl;
            }
            else
            {
                cout << "Invalid choice!" << endl;
            }
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