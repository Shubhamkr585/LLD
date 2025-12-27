#pragma once

#include <iostream>
#include <string>
#include "strategy_interface.hpp"

using namespace std;


// THE CONTEXT 
class Navigator {
private:
    IRouteStrategy* strategy; // The current "Brain"

public:
    // We can set the strategy at runtime!
    void setStrategy(IRouteStrategy* newStrategy) {
        this->strategy = newStrategy;
    }

    void buildRoute(string A, string B) {
        if (strategy) {
            strategy->buildRoute(A, B);
        } else {
            cout << "No strategy selected!" << endl;
        }
    }
};  