
#include "beverage_maker_interface.hpp"




// 1. Tea Implementation
class Tea : public BeverageMaker {
public:
    void brew() override {
        cout << " Steeping the tea bags..." << endl;
    }

    void addCondiments() override {
        cout << " Adding lemon..." << endl;
    }
};

// 2. Coffee Implementation
class Coffee : public BeverageMaker {
public:
    void brew() override {
        cout << "Dripping coffee through filter..." << endl;
    }

    void addCondiments() override {
        cout << " Adding sugar and milk..." << endl;
    }
};