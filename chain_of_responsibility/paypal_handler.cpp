// paypal_handler.cpp
#include "paypal_handler.hpp"
#include <iostream>

using namespace std;

PayPalHandler::PayPalHandler(double initialBalance) : balance(initialBalance) {}

void PayPalHandler::handlePayment(double amount) {
    if (balance >= amount) {
        cout << "Paid $" << amount << " using PayPal." << endl;
    } else {
        cout << "PayPal insufficient (Balance: $" << balance << "). Passing to next..." << endl;
        if (nextHandler) {
            nextHandler->handlePayment(amount);
        } else {
            cout << " Payment Failed: No payment method could handle $" << amount << endl;
        }
    }
}