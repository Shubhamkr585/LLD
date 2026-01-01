#ifndef EMPTY_STATE_HPP
#define EMPTY_STATE_HPP

#include "state.hpp"

class VendingMachine;

/**
 * @brief The EmptyState class represents the state of the vending machine when it is out of items.
 */
class EmptyState : public State {
private:
    VendingMachine* vendingMachine; ///< Pointer to the VendingMachine context.

public:
    /**
     * @brief Construct a new Empty State object.
     * 
     * @param vendingMachine A pointer to the VendingMachine context.
     */
    EmptyState(VendingMachine* vendingMachine);

    /**
     * @brief Handles the action of inserting a coin.
     */
    void insertCoin() override;

    /**
     * @brief Handles the action of pressing the button.
     */
    void pressButton() override;

    /**
     * @brief Handles the action of dispensing an item.
     */
    void dispense() override;

    /**
     * @brief Handles the action of refilling the machine.
     */
    void refill() override;
};

#endif // EMPTY_STATE_HPP
