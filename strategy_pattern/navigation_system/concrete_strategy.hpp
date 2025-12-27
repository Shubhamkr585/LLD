#pragma once

#include <iostream>
#include <string>
#include "strategy_interface.hpp"

using namespace std;


// CONCRETE STRATEGY CLASS

class CarStrategy : public IRouteStrategy {
public:
    void buildRoute(string A, string B) override {
        cout << " Building route for Car: Using highways, avoiding traffic." << endl;
    }
};

class WalkingStrategy : public IRouteStrategy {
public:
    void buildRoute(string A, string B) override {
        cout << " Building route for Walking: Using sidewalks and parks." << endl;
    }
};

class PublicTransportStrategy : public IRouteStrategy {
public:
    void buildRoute(string A, string B) override {
        cout << "Building route for Bus: Calculating stops and schedules." << endl;
    }
};