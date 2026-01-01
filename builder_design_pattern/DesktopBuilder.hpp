#ifndef DESKTOP_BUILDER_HPP
#define DESKTOP_BUILDER_HPP

#include "Desktop.hpp"

class DesktopBuilder {
    Desktop* desktop;

public:
    DesktopBuilder();

    DesktopBuilder& setCPU(const std::string& cpu);
    DesktopBuilder& setRAM(int ram);
    DesktopBuilder& setStorage(int storage);
    DesktopBuilder& setGPU(const std::string& gpu);
    DesktopBuilder& enableWiFi();
    DesktopBuilder& enableBluetooth();

    Desktop* build();
};

#endif
