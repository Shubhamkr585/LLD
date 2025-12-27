// main.cpp
#include <bits/stdc++.h>
using namespace std;
#include "bank_handler.hpp"
#include "paypal_handler.hpp"
#include "bitcoin_handler.hpp"

int main() {
    // 1. Initialize Handlers with specific balances
    // Bank has $500
    PaymentHandler* bank = new BankHandler(500.0);
    // PayPal has $200
    PaymentHandler* paypal = new PayPalHandler(200.0);
    // Bitcoin has $1000
    PaymentHandler* bitcoin = new BitcoinHandler(1000.0);

    // 2. Create the Chain
    // Priority: Bank -> PayPal -> Bitcoin
    bank->setNext(paypal);
    paypal->setNext(bitcoin);

    // 3. Test Cases

    cout << "--- Attempting to pay $200 ---" << endl;
    // Bank ($500) can handle this.
    bank->handlePayment(200.0); 

    cout << "\n--- Attempting to pay $600 ---" << endl;
    // Bank ($500) fails -> PayPal ($200) fails -> Bitcoin ($1000) pays.
    bank->handlePayment(600.0);

    cout << "\n--- Attempting to pay $5000 ---" << endl;
    // Everyone fails.
    bank->handlePayment(5000.0);

    // Cleanup
    delete bank;
    delete paypal;
    delete bitcoin;

    return 0;
}