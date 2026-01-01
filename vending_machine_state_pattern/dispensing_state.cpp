#include "dispensing_state.hpp"
#include "vending_machine.hpp"
#include <iostream>

/**
 * @brief Construct a new Dispensing State:: Dispensing State object
 * 
 * @param vendingMachine A pointer to the VendingMachine context.
 */
DispensingState::DispensingState(VendingMachine* vendingMachine) {
    this->vendingMachine = vendingMachine;
}

/**
 * @brief Handles the action of inserting a coin.
 * 
 * In this state, inserting a coin is not allowed.
 */
void DispensingState::insertCoin() {
    std::cout << "Please wait, item is being dispensed" << std::endl;
}

/**
 * @brief Handles the action of pressing the button.
 * 
 * In this state, pressing the button has no effect.
 */
void DispensingState::pressButton() {
    std::cout << "Please wait, item is being dispensed" << std::endl;
}

/**
 * @brief Handles the action of dispensing an item.
 * 
 * This method is called after the button is pressed in the CoinInsertedState.
 * It dispenses the item and changes the state to NoCoinInsertedState or EmptyState.
 */
void DispensingState::dispense() {
    std::cout << "Dispensing item" << std::endl;
    vendingMachine->refill(vendingMachine->getCount() - 1);
    if (vendingMachine->getCount() > 0) {
        vendingMachine->setState(vendingMachine->getNoCoinInsertedState());
    } else {
        vendingMachine->setState(vendingMachine->getEmptyState());
    }
}

/**
 * @brief Handles the action of refilling the machine.
 * 
 * In this state, refilling is not allowed.
 */
void DispensingState::refill() {
    std::cout << "Cannot refill while dispensing" << std::endl;
}
