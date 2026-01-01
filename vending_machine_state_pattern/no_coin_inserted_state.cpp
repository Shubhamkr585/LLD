#include "no_coin_inserted_state.hpp"
#include "vending_machine.hpp"
#include <iostream>

/**
 * @brief Construct a new No Coin Inserted State:: No Coin Inserted State object
 * 
 * @param vendingMachine A pointer to the VendingMachine context.
 */
NoCoinInsertedState::NoCoinInsertedState(VendingMachine* vendingMachine) {
    this->vendingMachine = vendingMachine;
}

/**
 * @brief Handles the action of inserting a coin.
 * 
 * When a coin is inserted, the state of the vending machine changes to CoinInsertedState.
 */
void NoCoinInsertedState::insertCoin() {
    std::cout << "Coin inserted" << std::endl;
    vendingMachine->setState(vendingMachine->getCoinInsertedState());
}

/**
 * @brief Handles the action of pressing the button.
 * 
 * In this state, pressing the button has no effect.
 */
void NoCoinInsertedState::pressButton() {
    std::cout << "Please insert a coin first" << std::endl;
}

/**
 * @brief Handles the action of dispensing an item.
 * 
 * In this state, dispensing has no effect.
 */
void NoCoinInsertedState::dispense() {
    std::cout << "Please insert a coin first" << std::endl;
}

/**
 * @brief Handles the action of refilling the machine.
 * 
 * In this state, refilling is allowed.
 */
void NoCoinInsertedState::refill() {
    std::cout << "Machine refilled" << std::endl;
}
