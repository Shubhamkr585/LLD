#ifndef DESKTOP_HPP
#define DESKTOP_HPP

#include <string>
#include <iostream>

class Desktop {
    friend class DesktopBuilder;

    std::string cpu;
    int ram = 0;
    int storage = 0;
    std::string gpu;
    bool hasWifi = false;
    bool hasBluetooth = false;

public:
    void showSpecs();
};

#endif
