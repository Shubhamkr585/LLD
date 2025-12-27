#pragma once

#include <iostream>
using namespace std;

class BeverageMaker {
public:
    // THIS IS THE TEMPLATE METHOD.
    // It defines the algorithm steps in a specific order.
    // Notice it is NOT virtual. We don't want subclasses to change the ORDER.
    void makeBeverage() {
        boilWater();
        brew();           // Step 2: Delegate to subclass
        pourInCup();
        addCondiments();  // Step 4: Delegate to subclass
    }

    // --- Standard Steps (Implemented here) ---
    void boilWater() {
        cout << " Boiling water..." << endl;
    }

    void pourInCup() {
        cout << " Pouring into cup..." << endl;
    }

    // --- Variable Steps (Pure Virtual - Subclasses MUST implement) ---
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
    
    virtual ~BeverageMaker() {}
};