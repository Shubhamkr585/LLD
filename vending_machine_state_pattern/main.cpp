#include "vending_machine.hpp"
#include <iostream>

/**
 * @brief The main function demonstrates the functionality of the vending machine.
 * 
 * @return int The exit code.
 */
int main() {
    // Create a vending machine with 2 items
    VendingMachine vendingMachine(2);

    std::cout << "Current count: " << vendingMachine.getCount() << std::endl;

    // Try to press the button without inserting a coin
    vendingMachine.pressButton();

    // Insert a coin and press the button
    vendingMachine.insertCoin();
    vendingMachine.pressButton();

    std::cout << "Current count: " << vendingMachine.getCount() << std::endl;

    // Insert another coin and press the button
    vendingMachine.insertCoin();
    vendingMachine.pressButton();

    std::cout << "Current count: " << vendingMachine.getCount() << std::endl;

    // The machine is now empty, try to insert a coin
    vendingMachine.insertCoin();

    // Refill the machine
    vendingMachine.refill(3);

    // Insert a coin and press the button
    vendingMachine.insertCoin();
    vendingMachine.pressButton();

    std::cout << "Current count: " << vendingMachine.getCount() << std::endl;

    return 0;
}
