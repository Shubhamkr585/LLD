// paypal_handler.hpp
#pragma once
#include "payment_handler.hpp"

class PayPalHandler : public PaymentHandler {
private:
    double balance;

public:
    PayPalHandler(double initialBalance);
    void handlePayment(double amount) override;
};