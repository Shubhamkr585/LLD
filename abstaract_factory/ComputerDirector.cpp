#include "ComputerDirector.hpp"

void ComputerDirector::buildGamingPC(DesktopBuilder& builder) {
    builder.setCPU("Ryzen 9")
           .setRAM(64)
           .setStorage(2048)
           .setGPU("RTX 4090")
           .enableWiFi()
           .enableBluetooth();
}

void ComputerDirector::buildOfficePC(DesktopBuilder& builder) {
    builder.setCPU("Intel i5")
           .setRAM(8)
           .setStorage(512);
}

