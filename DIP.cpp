// //  BAD LLD

// class SmartSwitch {
// public:
//     // This function turns devices on
//     void turnOn(string deviceType) {
//         if (deviceType == "LightBulb") {
//             cout << "Turning on the Light Bulb..." << endl;
//         } else if (deviceType == "Fan") {
//             cout << "Starting the Fan..." << endl;
//         } else if (deviceType == "AC") {
//             cout << "Cooling the room with AC..." << endl;
//         }
//     }
// };

// class LightBulb {
// public:
//     void glow() { /*...*/ }
// };

// class Fan {
// public:
//     void spin() { /*...*/ }
// };

// class House {
// private:
//     SmartSwitch sw; // The house depends directly on this concrete class
//     LightBulb bulb;
//     Fan fan;

// public:
//     void manageDevices() {
//         sw.turnOn("LightBulb");
//         sw.turnOn("Fan");
//     }
// };


//  GOOD LLD - SOLID Compliant

#include <iostream>
#include <vector>
using namespace std;

// 1. Abstraction (Solves DIP)
// We create a common interface for ALL devices.
class IDevice {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~IDevice() {}
};

// 2. Concrete Classes (Solves SRP)
// Each device knows how to turn ITSELF on.
class LightBulb : public IDevice {
public:
    void turnOn() override { cout <<  Light is glowing" << endl; }
    void turnOff() override { cout << "Light is off" << endl; }
};

class Fan : public IDevice {
public:
    void turnOn() override { cout << " Fan is spinning" << endl; }
    void turnOff() override { cout << "Fan is stopped" << endl; }
};


// New feature added later? No problem! (Solves OCP)
class Heater : public IDevice {
public:
    void turnOn() override { cout << " Heater is warming up" << endl; }
    void turnOff() override { cout << "Heater is off" << endl; }
};

// 3. The Switch (The Client)
// It depends on the INTERFACE, not the specific devices.
class SmartSwitch {
private:
    vector<IDevice*> devices; // Aggregation ("Has-a")

public:
    void addDevice(IDevice* d) {
        devices.push_back(d);
    }

    void turnAllOn() {
        // Polymorphism does the magic here.
        // No if-else chains needed!
        for (IDevice* d : devices) {
            d->turnOn();
        }
    }
};

int main() {
    // Dependency Injection
    IDevice* bulb = new LightBulb();
    IDevice* fan = new Fan();
    IDevice* heater = new Heater(); // Added easily

    SmartSwitch sw;
    sw.addDevice(bulb);
    sw.addDevice(fan);
    sw.addDevice(heater);

    cout << "--- Turning everything on ---" << endl;
    sw.turnAllOn();

    delete bulb; delete fan; delete heater;
    return 0;
}