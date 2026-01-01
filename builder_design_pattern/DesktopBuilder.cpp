#include "DesktopBuilder.hpp"

DesktopBuilder::DesktopBuilder() {
    desktop = new Desktop();
}

DesktopBuilder& DesktopBuilder::setCPU(const std::string& cpu) {
    desktop->cpu = cpu;
    return *this;
}

DesktopBuilder& DesktopBuilder::setRAM(int ram) {
    desktop->ram = ram;
    return *this;
}

DesktopBuilder& DesktopBuilder::setStorage(int storage) {
    desktop->storage = storage;
    return *this;
}

DesktopBuilder& DesktopBuilder::setGPU(const std::string& gpu) {
    desktop->gpu = gpu;
    return *this;
}

DesktopBuilder& DesktopBuilder::enableWiFi() {
    desktop->hasWifi = true;
    return *this;
}

DesktopBuilder& DesktopBuilder::enableBluetooth() {
    desktop->hasBluetooth = true;
    return *this;
}

Desktop* DesktopBuilder::build() {
    Desktop* result = desktop;
    desktop = new Desktop();   // reset builder
    return result;
}
