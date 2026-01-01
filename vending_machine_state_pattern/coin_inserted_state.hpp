#ifndef COIN_INSERTED_STATE_HPP
#define COIN_INSERTED_STATE_HPP

#include "state.hpp"

class VendingMachine;

/**
 * @brief The CoinInsertedState class represents the state of the vending machine when a coin is inserted.
 */
class CoinInsertedState : public State {
private:
    VendingMachine* vendingMachine; ///< Pointer to the VendingMachine context.

public:
    /**
     * @brief Construct a new Coin Inserted State object.
     * 
     * @param vendingMachine A pointer to the VendingMachine context.
     */
    CoinInsertedState(VendingMachine* vendingMachine);

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

#endif // COIN_INSERTED_STATE_HPP
