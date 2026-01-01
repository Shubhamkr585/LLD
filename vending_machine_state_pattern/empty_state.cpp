#include "empty_state.hpp"
#include "vending_machine.hpp"
#include <iostream>

/**
 * @brief Construct a new Empty State:: Empty State object
 * 
 * @param vendingMachine A pointer to the VendingMachine context.
 */
EmptyState::EmptyState(VendingMachine* vendingMachine) {
    this->vendingMachine = vendingMachine;
}

/**
 * @brief Handles the action of inserting a coin.
 * 
 * In this state, inserting a coin has no effect.
 */
void EmptyState::insertCoin() {
    std::cout << "Machine is empty" << std::endl;
}

/**
 * @brief Handles the action of pressing the button.
 * 
 * In this state, pressing the button has no effect.
 */
void EmptyState::pressButton() {
    std::cout << "Machine is empty" << std::endl;
}

/**
 * @brief Handles the action of dispensing an item.
 * 
 * In this state, dispensing has no effect.
 */
void EmptyState::dispense() {
    std::cout << "Machine is empty" << std::endl;
}

/**
 * @brief Handles the action of refilling the machine.
 * 
 * This method refills the machine and changes the state to NoCoinInsertedState.
 */
void EmptyState::refill() {
    vendingMachine->refill(5); // Refill with 5 items
    std::cout << "Machine refilled" << std::endl;
    vendingMachine->setState(vendingMachine->getNoCoinInsertedState());
}
