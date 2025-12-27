// payment_handler.cpp
#include "payment_handler.hpp"

PaymentHandler::PaymentHandler() : nextHandler(nullptr) {}

PaymentHandler::~PaymentHandler() {}

void PaymentHandler::setNext(PaymentHandler* next) {
    this->nextHandler = next;
}