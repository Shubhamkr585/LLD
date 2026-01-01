#ifndef DISPENSING_STATE_HPP
#define DISPENSING_STATE_HPP

#include "state.hpp"

class VendingMachine;

/**
 * @brief The DispensingState class represents the state of the vending machine when it is dispensing an item.
 */
class DispensingState : public State {
private:
    VendingMachine* vendingMachine; ///< Pointer to the VendingMachine context.

public:
    /**
     * @brief Construct a new Dispensing State object.
     * 
     * @param vendingMachine A pointer to the VendingMachine context.
     */
    DispensingState(VendingMachine* vendingMachine);

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

#endif // DISPENSING_STATE_HPP
