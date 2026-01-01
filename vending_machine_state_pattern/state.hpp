#ifndef STATE_HPP
#define STATE_HPP

class VendingMachine; // Forward declaration

/**
 * @brief The State interface defines the behavior of the vending machine in different states.
 * 
 * This interface is implemented by all concrete state classes.
 */
class State {
public:
    /**
     * @brief Handles the action of inserting a coin.
     */
    virtual void insertCoin() = 0;

    /**
     * @brief Handles the action of pressing the button.
     */
    virtual void pressButton() = 0;

    /**
     * @brief Handles the action of dispensing an item.
     */
    virtual void dispense() = 0;

    /**
     * @brief Handles the action of refilling the machine.
     */
    virtual void refill() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~State() {}
};

#endif // STATE_HPP
