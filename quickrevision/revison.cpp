//Singleton

// eager initialisaiton 
class Singleton {
private:
    Singleton() {}
    static Singleton instance;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance() {
        return instance;
    }
};
// Definition outside the class
Singleton Singleton::instance;
int main(){
    Singleton obj=Singleton::getInstance();
    cout<<obj.sum(4,5);
}

// lazy initialisation 
class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx;
    Singleton() {}
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }
};
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;
int main(){
    Singleton* single1=Singleton::getInstance();
    Singleton* single2=Singleton::getInstance();
    cout<<(single1==single2);
}
// mayers 
// class Singleton {
// private:
//     Singleton() {}

// public:
//     Singleton(const Singleton&) = delete;
//     Singleton& operator=(const Singleton&) = delete;

//     static Singleton& getInstance() {
//         static Singleton instance;
//         return instance;
//     }
// };

// simple factory 
#include <iostream>
#include <memory>
using namespace std;

class Vehicle {
public:
    virtual void drive() = 0;
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    void drive() override {
        cout << "Driving Car\n";
    }
};

class Bike : public Vehicle {
public:
    void drive() override {
        cout << "Riding Bike\n";
    }
};

class VehicleFactory {
public:
    static unique_ptr<Vehicle> createVehicle(const string& type) {
        if (type == "car")
            return make_unique<Car>();

        if (type == "bike")
            return make_unique<Bike>();

        return nullptr;
    }
};

int main() {
    auto v = VehicleFactory::createVehicle("car");
    v->drive();
}

// Factory method 


// Product
class Vehicle {
public:
    virtual void drive() = 0;
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    void drive() override {
        cout << "Driving Car\n";
    }
};

class Bike : public Vehicle {
public:
    void drive() override {
        cout << "Riding Bike\n";
    }
};

// Creator
class VehicleFactory {
public:
    virtual Vehicle* createVehicle() = 0;
    virtual ~VehicleFactory() = default;
};

class CarFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() override {
        return new Car();
    }
};

class BikeFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() override {
        return new Bike();
    }
};

int main() {
    VehicleFactory* factory = new CarFactory();

    Vehicle* vehicle = factory->createVehicle();
    vehicle->drive();
    factory=new BikeFactory();
    vehicle=factory->createVehicle();
    vehicle->drive();
    

    delete vehicle;
    delete factory;
}

// Factory Method defines an interface for creating an object,
// but lets subclasses decide which concrete object to instantiate.

// Simple Factory = one factory, condition decides.
// Factory Method = subclass decides.