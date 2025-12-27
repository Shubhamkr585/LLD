// bitcoin_handler.hpp
#pragma once
#include "payment_handler.hpp"

class BitcoinHandler : public PaymentHandler {
private:
    double balance;

public:
    BitcoinHandler(double initialBalance);
    void handlePayment(double amount) override;
};