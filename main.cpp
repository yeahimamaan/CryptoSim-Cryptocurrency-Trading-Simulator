#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
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

    // File handling to save transaction histor to file
    void saveToFile(string filename)
    {
        ofstream file(filename, ios::app);
        file << type << "," << coinName << "," << quantity << ","
             << priceAtTime << "," << timestamp << endl;
        file.close();
    }

    // File handling loads and displays all transactions history from file
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

class Wallet
{
private:
    double usdtBalance;
    map<string, double> holdings;

public:
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
        for (auto &h : holdings)
        {
            cout << h.first << ": " << h.second << endl;
        }
    }

    double getBalance() const { return usdtBalance; }
    map<string, double> getHoldings() const { return holdings; }
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
        coins.push_back(Coin("Zcoin", "ZEE", 45000.0));
        coins.push_back(Coin("ABCoin", "AB", 45000.0));
    }

    void displayMarket()
    {
        cout << "=== Market ===" << endl;
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
            {
                return &coins[i];
            }
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
                cout << "Price updated!" << endl;
            }
        }
    }
};

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
        cout << "=== Portfolio ===" << endl;
        totalValue = 0;
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

class PriceHistory
{
private:
    string coinSymbol;
    vector<double> prices;

public:
    PriceHistory(string symbol) : coinSymbol(symbol) {}

    void addPrice(double price)
    {
        prices.push_back(price);
    }

    void displayHistory()
    {
        cout << "=== Price History for " << coinSymbol << " ===" << endl;
        for (int i = 0; i < prices.size(); i++)
        {
            cout << "Entry " << i + 1 << ": $" << prices[i] << endl;
        }
    }

    double getHighest()
    {
        double highest = prices[0];
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i] > highest)
                highest = prices[i];
        }
        return highest;
    }

    double getLowest()
    {
        double lowest = prices[0];
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i] < lowest)
                lowest = prices[i];
        }
        return lowest;
    }
};

class Account
{
protected:
    string username;
    string password;

public:
    Account(string u, string p) : username(u), password(p) {}

    bool login(string u, string p)
    {
        return (username == u && password == p);
    }

    string getUsername() const { return username; }
};

class User : public Account
{
private:
    Wallet wallet;
    Portfolio portfolio;
    vector<Transaction> transactionHistory;

public:
    User(string u, string p, double balance)
        : Account(u, p), wallet(balance) {}

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
            Transaction t("buy", symbol, qty, coin->getPrice(), "2024-01-01");
            t.saveToFile("transactions.txt");
            transactionHistory.push_back(t);
            cout << "Purchase successful!" << endl;
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
            Transaction t("sell", symbol, qty, coin->getPrice(), "2024-01-01");
            t.saveToFile("transactions.txt");
            transactionHistory.push_back(t);
            cout << "Sale successful!" << endl;
        }
    }

    void viewWallet() { wallet.displayWallet(); }

    void viewPortfolio(Market &market)
    {
        portfolio.updateHoldings(wallet.getHoldings());
        portfolio.displayPortfolio(market);
    }

    void viewHistory()
    {
        Transaction::loadFromFile("transactions.txt");
    }
};

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
        cout << "=== Admin Panel ===" << endl;
        cout << "1. Add Coin" << endl;
        cout << "2. Update Coin Price" << endl;
        cout << "3. Exit Admin Panel" << endl;
    }
};
class Exchange
{
private:
    Market market;
    User user;
    Admin admin;

public:
    Exchange() : user("user", "123", 100000), admin("admin", "admin", "999") {}

    void start()
    {
        int choice;
        do
        {
            cout << "\n=== Crypto Exchange ===" << endl;
            cout << "1. View Market" << endl;
            cout << "2. Buy Coin" << endl;
            cout << "3. Sell Coin" << endl;
            cout << "4. View Wallet" << endl;
            cout << "5. View Portfolio" << endl;
            cout << "6. View Transactions" << endl;
            cout << "7. Admin Panel" << endl;
            cout << "0. Exit" << endl;
            cin >> choice;

            if (choice == 1)
                market.displayMarket();

            else if (choice == 2)
            {
                string sym; double qty;
                cout << "Enter Symbol and Quantity: ";
                cin >> sym >> qty;
                user.buy(market, sym, qty);
            }

            else if (choice == 3)
            {
                string sym; double qty;
                cout << "Enter Symbol and Quantity: ";
                cin >> sym >> qty;
                user.sell(market, sym, qty);
            }

            else if (choice == 4)
                user.viewWallet();

            else if (choice == 5)
                user.viewPortfolio(market);

            else if (choice == 6)
                user.viewHistory();

            else if (choice == 7)
                adminMenu();
        } while (choice != 0);
    }

    void adminMenu()
    {
        int choice;
        do
        {
            admin.displayAdminMenu();
            cin >> choice;

            if (choice == 1)
            {
                string name, symbol;
                double price;
                cout << "Enter name symbol price: ";
                cin >> name >> symbol >> price;
                admin.addCoin(market, name, symbol, price);
            }
            else if (choice == 2)
            {
                string symbol; double price;
                cout << "Enter symbol and new price: ";
                cin >> symbol >> price;
                admin.updatePrice(market, symbol, price);
            }

        } while (choice != 3);
    }
};
int main()
{
    Exchange ex;   
    ex.start();    
    return 0;
}
