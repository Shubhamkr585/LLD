// payment_handler.hpp
#pragma once
#include <iostream>
#include <string>

class PaymentHandler {
protected:
    PaymentHandler* nextHandler; // Pointer to the next method in the chain

public:
    PaymentHandler();
    virtual ~PaymentHandler();

    // Setup the chain
    void setNext(PaymentHandler* next);

    // The core logic
    virtual void handlePayment(double amount) = 0;
};