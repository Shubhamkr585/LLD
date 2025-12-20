#include "Desktop.hpp"

void Desktop::showSpecs() {
    std::cout << "-------------------------" << std::endl;
    std::cout << "CPU: " << cpu << std::endl;
    std::cout << "RAM: " << ram << "GB" << std::endl;
    std::cout << "Storage: " << storage << "GB" << std::endl;
    if (!gpu.empty())
        std::cout << "GPU: " << gpu << std::endl;
    if (hasWifi)
        std::cout << "WiFi: Yes" << std::endl;
    if (hasBluetooth)
        std::cout << "Bluetooth: Yes" << std::endl;
    std::cout << "-------------------------" << std::endl;
}
