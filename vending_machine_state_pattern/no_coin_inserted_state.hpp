#ifndef NO_COIN_INSERTED_STATE_HPP
#define NO_COIN_INSERTED_STATE_HPP

#include "state.hpp"

class VendingMachine;

/**
 * @brief The NoCoinInsertedState class represents the state of the vending machine when no coin is inserted.
 */
class NoCoinInsertedState : public State {
private:
    VendingMachine* vendingMachine; ///< Pointer to the VendingMachine context.

public:
    /**
     * @brief Construct a new No Coin Inserted State object.
     * 
     * @param vendingMachine A pointer to the VendingMachine context.
     */
    NoCoinInsertedState(VendingMachine* vendingMachine);

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

#endif // NO_COIN_INSERTED_STATE_HPP
