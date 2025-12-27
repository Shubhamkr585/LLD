#include "beverage_maker_interface.hpp"
#include "beverage_maker_concerte.cpp"
#include <iostream>
using namespace std;


int main() {
    cout << "--- Making Tea ---" << endl;
    BeverageMaker* myTea = new Tea();
    myTea->makeBeverage(); 
    // Output: Boil -> Steep -> Pour -> Lemon

    cout << "\n--- Making Coffee ---" << endl;
    BeverageMaker* myCoffee = new Coffee();
    myCoffee->makeBeverage();
    // Output: Boil -> Drip -> Pour -> Sugar/Milk

    delete myTea;
    delete myCoffee;
    return 0;
}