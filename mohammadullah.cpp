#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Person {
protected:
    string name;

public:
    Person(string n = "") {
        name = n;
    }

    string getName() {
        return name;
    }
};

class Account {
protected:
    int accountNumber;
    int pin;
    double balance;

public:
    Account(int acc = 0, int p = 0, double b = 0) {
        accountNumber = acc;
        pin = p;
        balance = b;
    }

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    double getBalance() {
        return balance;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    bool verifyPin(int enteredPin) {
        return pin == enteredPin;
    }

    void changePin(int newPin) {
        pin = newPin;
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int acc, int p, double b)
        : Account(acc, p, b) {}
};

class CurrentAccount : public Account {
public:
    CurrentAccount(int acc, int p, double b)
        : Account(acc, p, b) {}
};

class Transaction {
private:
    string type;
    double amount;

public:
    Transaction(string t, double a) {
        type = t;
        amount = a;
    }

    void display() {
        cout << type << " : Rs. " << amount << endl;
    }
};

class Customer : public Person {
private:
    Account* account;
    vector<Transaction> history;

public:
    Customer(string n, Account* acc)
        : Person(n) {
        account = acc;
    }

    Account* getAccount() {
        return account;
    }

    void addTransaction(string type, double amount) {
        history.push_back(Transaction(type, amount));
    }

    void showHistory() {
        cout << "\nTransaction History\n";

        for (auto t : history) {
            t.display();
        }
    }
};

class Admin : public Person {
public:
    Admin(string n) : Person(n) {}

    void showAdminPanel() {
        cout << "\n===== ADMIN PANEL =====\n";
        cout << "System Maintenance Running...\n";
    }
};

class FileManager {
public:
    static void saveData(Customer& c) {
        ofstream file("bank.txt", ios::app);

        file << c.getName() << " "
             << c.getAccount()->getAccountNumber() << " "
             << c.getAccount()->getBalance() << endl;

        file.close();
    }
};

class Bank {
private:
    vector<Customer> customers;

public:
    void addCustomer(Customer c) {
        customers.push_back(c);
    }

    Customer* login(int acc, int pin) {
        for (int i = 0; i < customers.size(); i++) {

            if (customers[i].getAccount()->getAccountNumber() == acc &&
                customers[i].getAccount()->verifyPin(pin)) {

                return &customers[i];
            }
        }

        return nullptr;
    }
};

class ATM {
private:
    Bank bank;

public:
    ATM() {
        Account* acc1 = new SavingsAccount(1001, 1234, 5000);

        Customer c1("Ali", acc1);

        bank.addCustomer(c1);
    }

    void start() {
        int acc, pin;

        cout << "===== ATM MANAGEMENT SYSTEM =====\n";

        cout << "Enter Account Number: ";
        cin >> acc;

        cout << "Enter PIN: ";
        cin >> pin;

        Customer* user = bank.login(acc, pin);

        if (user == nullptr) {
            cout << "Invalid Account or PIN\n";
            return;
        }

        int choice;

        do {
            cout << "\n===== MENU =====\n";

            cout << "1. Check Balance\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Change PIN\n";
            cout << "5. Transaction History\n";
            cout << "6. Exit\n";

            cout << "Enter Choice: ";
            cin >> choice;

            switch (choice) {

            case 1:
                cout << "Balance: Rs. "
                     << user->getAccount()->getBalance() << endl;
                break;

            case 2: {
                double amount;

                cout << "Enter Deposit Amount: ";
                cin >> amount;

                user->getAccount()->deposit(amount);

                user->addTransaction("Deposit", amount);

                cout << "Deposit Successful\n";

                break;
            }

            case 3: {
                double amount;

                cout << "Enter Withdraw Amount: ";
                cin >> amount;

                if (user->getAccount()->withdraw(amount)) {

                    user->addTransaction("Withdraw", amount);

                    cout << "Withdrawal Successful\n";
                }

                else {
                    cout << "Insufficient Balance\n";
                }

                break;
            }

            case 4: {
                int newPin;

                cout << "Enter New PIN: ";
                cin >> newPin;

                user->getAccount()->changePin(newPin);

                cout << "PIN Changed Successfully\n";

                break;
            }

            case 5:
                user->showHistory();
                break;

            case 6:
                FileManager::saveData(*user);

                cout << "Thank You For Using ATM\n";
                break;

            default:
                cout << "Invalid Choice\n";
            }

        } while (choice != 6);
    }
};

int main() {

    ATM atm;

    atm.start();

    return 0;
}