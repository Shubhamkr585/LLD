#include <iostream>
#include <string>
#include <iomanip> // For formatting currency

using namespace std;

// ==========================================
// 1. The Component Interface (FoodItem)
// ==========================================
class FoodItem {
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
    virtual ~FoodItem() {}
};

// ==========================================
// 2. Concrete Components (Base Items)
// ==========================================
class PlainPizza : public FoodItem {
public:
    string getDescription() override {
        return "Plain Pizza";
    }
    double getCost() override {
        return 5.00;
    }
};

class PlainBurger : public FoodItem {
public:
    string getDescription() override {
        return "Plain Burger";
    }
    double getCost() override {
        return 4.00;
    }
};

// ==========================================
// 3. The Base Decorator
// It implements the interface AND holds a pointer to the next layer down.
// ==========================================
class ToppingDecorator : public FoodItem {
protected:
    FoodItem* wrappee; // The item we are wrapping

public:
    ToppingDecorator(FoodItem* item) : wrappee(item) {}

    // Standard behavior: just delegate to the wrappee.
    // Subclasses will override this to add their own behavior.
    string getDescription() override {
        return wrappee->getDescription();
    }
    double getCost() override {
        return wrappee->getCost();
    }

    // Important: When a decorator dies, it shouldn't necessarily delete what's inside, 
    // as that might be managed elsewhere. But for simple examples, we often leave it.
    ~ToppingDecorator() {
       // In a complex system, memory management of decorated chains needs care.
    }
};

// ==========================================
// 4. Concrete Decorators (The Toppings)
// ==========================================

// --- Cheese (+ $1.00) ---
class Cheese : public ToppingDecorator {
public:
    Cheese(FoodItem* item) : ToppingDecorator(item) {}

    string getDescription() override {
        // 1. Get description from inside layer
        // 2. Add my description
        return wrappee->getDescription() + ", Extra Cheese";
    }

    double getCost() override {
        // 1. Get cost from inside layer
        // 2. Add my cost
        return wrappee->getCost() + 1.00;
    }
};

// --- Sauce (+ $0.50) ---
class Sauce : public ToppingDecorator {
public:
    Sauce(FoodItem* item) : ToppingDecorator(item) {}

    string getDescription() override {
        return wrappee->getDescription() + ", Special Sauce";
    }

    double getCost() override {
        return wrappee->getCost() + 0.50;
    }
};

// --- Mayonnaise (+ $0.75) ---
class Mayo : public ToppingDecorator {
public:
    Mayo(FoodItem* item) : ToppingDecorator(item) {}

    string getDescription() override {
        return wrappee->getDescription() + ", Mayonnaise";
    }

    double getCost() override {
        return wrappee->getCost() + 0.75;
    }
};

// Helper function to print receipt
void printReceipt(FoodItem* item) {
    cout << "ORDER: " << item->getDescription() << endl;
    // Set output to 2 decimal places for currency
    cout << "TOTAL: $" << fixed << setprecision(2) << item->getCost() << endl;
    cout << "-----------------------------" << endl;
}

// ==========================================
// 5. The Client (The Ordering Kiosk)
// ==========================================
int main() {
    // --- Order 1: A simple burger ---
    FoodItem* order1 = new PlainBurger();
    printReceipt(order1);

    // --- Order 2: Pizza with Cheese and Sauce ---
    // 1. Start with Pizza ($5.00)
    FoodItem* pizza = new PlainPizza();
    
    // 2. Wrap it in Cheese (+$1.00)
    // 'pizza' now points to the Cheese wrapper, which holds the PlainPizza inside.
    pizza = new Cheese(pizza); 

    // 3. Wrap that whole thing in Sauce (+$0.50)
    // 'pizza' now points to the Sauce wrapper.
    pizza = new Sauce(pizza);

    // The chain looks like: Sauce -> Cheese -> PlainPizza
    printReceipt(pizza); 
    // Expected Cost: 5.00 + 1.00 + 0.50 = $6.50


    // --- Order 3: Burger with DOUBLE Mayo (Solving the rigid inheritance problem) ---
    FoodItem* burger = new PlainBurger(); // $4.00
    burger = new Mayo(burger);            // +$0.75
    burger = new Mayo(burger);            // +$0.75 again!
    
    printReceipt(burger);
    // Expected Cost: 4.00 + 0.75 + 0.75 = $5.50

    // Cleanup (In real code, use smart pointers to manage this chain deletion automatically)
    // Deleting the outermost layer won't automatically delete inner layers 
    // unless the destructor is programmed to do so. For simplicity here, we skip complex cleanup.
    return 0;
}