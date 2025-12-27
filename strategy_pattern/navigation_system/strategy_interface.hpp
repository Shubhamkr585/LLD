#pragma once

#include <iostream>
#include <string>
using namespace std;

// The Abstract Strategy
class IRouteStrategy {
public:
    virtual void buildRoute(string A, string B) = 0;
    virtual ~IRouteStrategy() {}
};