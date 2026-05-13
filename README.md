CryptoSim — Cryptocurrency Trading Simulator
CryptoSim is a console-based cryptocurrency trading simulator built in C++ as an Object-Oriented Programming project. It simulates a real crypto exchange where users can register accounts, trade cryptocurrencies, manage their portfolio and track their transaction history.

Features

Multi-user registration and login system with username and password authentication
Buy and sell cryptocurrencies at live market prices
Personal wallet for each user tracking USD balance and coin holdings
Portfolio tracker showing total value of holdings at current market prices
Transaction history saved to individual files per user using file handling
Historical price data for each coin showing yearly performance
Admin panel with password protection to add new coins and update prices
Trade statistics tracking total buys and sells across the system


Built With

Language: C++
Concepts: Object Oriented Programming, File Handling, Inheritance, Composition, Encapsulation


Classes
ClassDescriptionCoinRepresents a cryptocurrency with name, symbol and pricePriceHistoryStores yearly historical prices for each coinTransactionRecords individual trades and handles file saving and loadingWalletManages user USD balance and coin holdingsAccountBase class for User and Admin with login functionalityMarketCentral marketplace listing all available coinsPortfolioCalculates and displays total value of user holdingsUserRegistered user with wallet, portfolio and trade historyAdminAdministrator with ability to manage coins and pricesTradeManagerTracks overall trading statistics across the systemExchangeMain controller managing all users, admin and menus

How To Run

Clone the repository
Place all .h files and main.cpp in the same folder
Compile using g++:

g++ main.cpp -o CryptoSim

Run:

./CryptoSim

Default Admin Credentials
Username: admin
Password: admin123

Project Structure
CryptoSim/
├── main.cpp
├── Coin.h
├── PriceHistory.h
├── Transaction.h
├── Wallet.h
└── Account.h

Developed as a semester OOP project in C++
