// bitcoin_handler.cpp
#include "bitcoin_handler.hpp"
#include <iostream>

using namespace std;

BitcoinHandler::BitcoinHandler(double initialBalance) : balance(initialBalance) {}

void BitcoinHandler::handlePayment(double amount) {
    if (balance >= amount) {
        cout << " Paid $" << amount << " using Bitcoin." << endl;
    } else {
        cout << " Bitcoin insufficient. Passing to next..." << endl;
        if (nextHandler) {
            nextHandler->handlePayment(amount);
        } else {
            cout << " Payment Failed: All methods exhausted." << endl;
        }
    }
}