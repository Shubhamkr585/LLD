// bank_handler.hpp
#pragma once
#include "payment_handler.hpp"

class BankHandler : public PaymentHandler {
private:
    double balance; // User's current bank balance

public:
    BankHandler(double initialBalance);
    void handlePayment(double amount) override;
};