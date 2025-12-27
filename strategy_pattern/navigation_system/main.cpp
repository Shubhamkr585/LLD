
#include <iostream>
#include <string>
#include "navigator.hpp"
#include "concrete_strategy.hpp"

using namespace std;


int main() {
    Navigator* googleMaps = new Navigator();

    // 1. User selects "Car"
    cout << "--- Selecting Car Mode ---" << endl;
    googleMaps->setStrategy(new CarStrategy());
    googleMaps->buildRoute("Home", "Office");

    // 2. User selects "Walking" (Context switches behavior instantly)
    cout << "\n--- Selecting Walking Mode ---" << endl;
    googleMaps->setStrategy(new WalkingStrategy());
    googleMaps->buildRoute("Home", "Office");

    // 3. User selects "Bus"
    cout << "\n--- Selecting Public Transport ---" << endl;
    googleMaps->setStrategy(new PublicTransportStrategy());
    googleMaps->buildRoute("Home", "Office");

    // Cleanup (Note: In real code, manage memory for the old strategies!)
    delete googleMaps;
    return 0;
}