#include <iostream>
#include <string>
using namespace std;

// ==========================================
// 1. The Implementation Interface (Payment Gateway)
// ==========================================
class PaymentGateway {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentGateway() {}
};

// ==========================================
// 2. Concrete Implementations (Specific Gateways)
// ==========================================
class Paytm : public PaymentGateway {
public:
    void processPayment(double amount) override {
        cout << "   [Paytm] Processing payment of Rs " << amount << " via Wallet." << endl;
    }
};

class UPI : public PaymentGateway {
public:
    void processPayment(double amount) override {
        cout << "   [UPI] Request sent to VPA. Processing Rs " << amount << "..." << endl;
    }
};

class CreditCard : public PaymentGateway {
public:
    void processPayment(double amount) override {
        cout << "   [Card] Authenticating OTP... Charged Rs " << amount << "." << endl;
    }
};

// ==========================================
// 3. The Abstraction (The Order)
// It holds the BRIDGE to the PaymentGateway
// ==========================================
class Order {
protected:
    PaymentGateway* paymentGateway; // <--- THE BRIDGE

public:
    // We inject the specific gateway at runtime
    Order(PaymentGateway* pg) : paymentGateway(pg) {}

    virtual void placeOrder(double amount) = 0;
    virtual ~Order() {}
};

// ==========================================
// 4. Refined Abstractions (Specific Order Types)
// ==========================================

// Food Order Logic
class FoodOrder : public Order {
public:
    FoodOrder(PaymentGateway* pg) : Order(pg) {}


    void placeOrder(double amount) override {
        cout << "🍔 Processing Food Order..." << endl;
        cout << "   -> Validating Restaurant Availability..." << endl;
        // Delegate the actual money handling to the implementation
        paymentGateway->processPayment(amount);
        cout << "   -> Order Placed successfully!\n" << endl;
    }
};

// Instamart (Grocery) Logic
class InstamartOrder : public Order {
public:
    InstamartOrder(PaymentGateway* pg) : Order(pg) {}

    void placeOrder(double amount) override {
        cout << "🥦 Processing Instamart Order..." << endl;
        cout << "   -> Checking Inventory for Items..." << endl;
        cout << "   -> Adding Delivery Fee..." << endl;
        // Delegate payment
        paymentGateway->processPayment(amount + 50); // Adding delivery charge logic
        cout << "   -> Grocery Order Placed!\n" << endl;
    }
};

// ==========================================
// 5. The Client (Swiggy App)
// ==========================================
int main() {
    // 1. Create Payment Methods (The Implementations)
    PaymentGateway* paytm = new Paytm();
    PaymentGateway* upi = new UPI();
    PaymentGateway* card = new CreditCard();

    // 2. Scenario A: User orders Pizza using UPI
    Order* myLunch = new FoodOrder(upi);
    myLunch->placeOrder(450.00);

    // 3. Scenario B: User orders Groceries using Credit Card
    Order* weeklyGroceries = new InstamartOrder(card);
    weeklyGroceries->placeOrder(1200.00);

    // 4. Scenario C: Swiggy introduces 'Genie' (Package Delivery) tomorrow?
    // We just create a 'GenieOrder' class. We DO NOT touch the Payment classes.
    // Order* package = new GenieOrder(paytm); -> Works instantly!

    // Cleanup
    delete paytm; delete upi; delete card;
    delete myLunch; delete weeklyGroceries;

    return 0;
}