#ifndef VENDING_MACHINE_HPP
#define VENDING_MACHINE_HPP

#include "state.hpp"

// Forward declarations of state classes
class NoCoinInsertedState;
class CoinInsertedState;
class DispensingState;
class EmptyState;

/**
 * @brief The VendingMachine class is the context class that holds the current state.
 * 
 * It delegates the requests to the current state object.
 */
class VendingMachine {
private:
    State* currentState;        ///< Pointer to the current state of the vending machine.
    int count;                  ///< Number of items in the vending machine.
    State* noCoinInsertedState; ///< Pointer to the NoCoinInsertedState.
    State* coinInsertedState;   ///< Pointer to the CoinInsertedState.
    State* dispensingState;     ///< Pointer to the DispensingState.
    State* emptyState;          ///< Pointer to the EmptyState.

public:
    /**
     * @brief Construct a new Vending Machine object.
     * 
     * @param count The initial number of items in the vending machine.
     */
    VendingMachine(int count);

    /**
     * @brief Destroy the Vending Machine object.
     */
    ~VendingMachine();

    /**
     * @brief Handles the action of inserting a coin.
     */
    void insertCoin();

    /**
     * @brief Handles the action of pressing the button.
     */
    void pressButton();

    /**
     * @brief Handles the action of dispensing an item.
     */
    void dispense();

    /**
     * @brief Refills the vending machine with a given number of items.
     * 
     * @param count The number of items to add.
     */
    void refill(int count);

    /**
     * @brief Sets the current state of the vending machine.
     * 
     * @param state The new state.
     */
    void setState(State* state);

    /**
     * @brief Gets the number of items in the vending machine.
     * 
     * @return int The number of items.
     */
    int getCount() const;

    /**
     * @brief Gets the NoCoinInsertedState object.
     * 
     * @return State* A pointer to the NoCoinInsertedState.
     */
    State* getNoCoinInsertedState() const;

    /**
     * @brief Gets the CoinInsertedState object.
     * 
     * @return State* A pointer to the CoinInsertedState.
     */
    State* getCoinInsertedState() const;

    /**
     * @brief Gets the DispensingState object.
     * 
     * @return State* A pointer to the DispensingState.
     */
    State* getDispensingState() const;

    /**
     * @brief Gets the EmptyState object.
     * 
     * @return State* A pointer to the EmptyState.
     */
    State* getEmptyState() const;
};

#endif // VENDING_MACHINE_HPP
