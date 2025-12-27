// bank_handler.cpp
#include "bank_handler.hpp"
#include <iostream>

using namespace std;

BankHandler::BankHandler(double initialBalance) : balance(initialBalance) {}

void BankHandler::handlePayment(double amount) {
    if (balance >= amount) {
        cout << " Paid $" << amount << " using Bank Account." << endl;
    } else {
        cout << " Bank Account insufficient (Balance: $" << balance << "). Passing to next..." << endl;
        if (nextHandler) {
            nextHandler->handlePayment(amount);
        } else {
            cout << " Payment Failed: No payment method could handle $" << amount << endl;
        }
    }
}