#include "coin_inserted_state.hpp"
#include "vending_machine.hpp"
#include <iostream>

/**
 * @brief Construct a new Coin Inserted State:: Coin Inserted State object
 * 
 * @param vendingMachine A pointer to the VendingMachine context.
 */
CoinInsertedState::CoinInsertedState(VendingMachine* vendingMachine) {
    this->vendingMachine = vendingMachine;
}

/**
 * @brief Handles the action of inserting a coin.
 * 
 * In this state, inserting another coin is not allowed.
 */
void CoinInsertedState::insertCoin() {
    std::cout << "Coin already inserted" << std::endl;
}

/**
 * @brief Handles the action of pressing the button.
 * 
 * When the button is pressed, the state of the vending machine changes to DispensingState.
 */
void CoinInsertedState::pressButton() {
    std::cout << "Button pressed" << std::endl;
    vendingMachine->setState(vendingMachine->getDispensingState());
}

/**
 * @brief Handles the action of dispensing an item.
 * 
 * In this state, dispensing is not directly possible. The user has to press the button.
 */
void CoinInsertedState::dispense() {
    std::cout << "Press the button to dispense" << std::endl;
}

/**
 * @brief Handles the action of refilling the machine.
 * 
 * In this state, refilling is not allowed.
 */
void CoinInsertedState::refill() {
    std::cout << "Cannot refill while in operation" << std::endl;
}
