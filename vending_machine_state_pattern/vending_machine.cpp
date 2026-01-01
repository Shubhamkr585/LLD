#include "vending_machine.hpp"
#include "no_coin_inserted_state.hpp"
#include "coin_inserted_state.hpp"
#include "dispensing_state.hpp"
#include "empty_state.hpp"

/**
 * @brief Construct a new Vending Machine:: Vending Machine object
 * 
 * @param count The initial number of items in the vending machine.
 */
VendingMachine::VendingMachine(int count) {
    // Create instances of all states
    noCoinInsertedState = new NoCoinInsertedState(this);
    coinInsertedState = new CoinInsertedState(this);
    dispensingState = new DispensingState(this);
    emptyState = new EmptyState(this);

    this->count = count;
    // Set the initial state based on the count
    if (count > 0) {
        currentState = noCoinInsertedState;
    } else {
        currentState = emptyState;
    }
}

/**
 * @brief Destroy the Vending Machine:: Vending Machine object
 * 
 * Deletes all state objects.
 */
VendingMachine::~VendingMachine() {
    delete noCoinInsertedState;
    delete coinInsertedState;
    delete dispensingState;
    delete emptyState;
}

/**
 * @brief Delegates the insertCoin action to the current state.
 */
void VendingMachine::insertCoin() {
    currentState->insertCoin();
}

/**
 * @brief Delegates the pressButton action to the current state and then dispenses.
 */
void VendingMachine::pressButton() {
    currentState->pressButton();
    currentState->dispense();
}

/**
 * @brief This method is not used directly. The dispense action is handled by the state.
 */
void VendingMachine::dispense() {
    // This is handled by the state
}

/**
 * @brief Refills the vending machine with a given number of items.
 * 
 * @param count The number of items to add.
 */
void VendingMachine::refill(int count) {
    this->count = count;
    if(this->count > 0){
        setState(getNoCoinInsertedState());
    }
}

/**
 * @brief Sets the current state of the vending machine.
 * 
 * @param state The new state.
 */
void VendingMachine::setState(State* state) {
    currentState = state;
}

/**
 * @brief Gets the number of items in the vending machine.
 * 
 * @return int The number of items.
 */
int VendingMachine::getCount() const {
    return count;
}

/**
 * @brief Gets the NoCoinInsertedState object.
 * 
 * @return State* A pointer to the NoCoinInsertedState.
 */
State* VendingMachine::getNoCoinInsertedState() const {
    return noCoinInsertedState;
}

/**
 * @brief Gets the CoinInsertedState object.
 * 
 * @return State* A pointer to the CoinInsertedState.
 */
State* VendingMachine::getCoinInsertedState() const {
    return coinInsertedState;
}

/**
 * @brief Gets the DispensingState object.
 * 
 * @return State* A pointer to the DispensingState.
 */
State* VendingMachine::getDispensingState() const {
    return dispensingState;
}

/**
 * @brief Gets the EmptyState object.
 * 
 * @return State* A pointer to the EmptyState.
 */
State* VendingMachine::getEmptyState() const {
    return emptyState;
}
