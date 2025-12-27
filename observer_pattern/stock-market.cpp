#include <bits/stdc++.h>
using namespace std;

// --- 1. The Observer Interface (The Subscriber) ---
class IObserver {
public:
    // This is the message the subscriber gets
    virtual void update(float price) = 0;
    virtual ~IObserver() {}
};

// --- 2. The Subject Interface (The Publisher) ---
class ISubject {
public:
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
    virtual ~ISubject() {}
};

// --- 3. Concrete Subject (Stock Market) ---
class StockMarket : public ISubject {
private:
    vector<IObserver*> observers; // List of subscribers
    float price;

public:

    void attach(IObserver* observer) override {
        observers.push_back(observer);
    }

    void detach(IObserver* observer) override {
        // Standard C++ idiom to remove an item from a vector
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // The Magic Method: Loop through list and tell everyone
    void notify() override {
        for (IObserver* obs : observers) {
            obs->update(price);
        }
    }

    // Business Logic triggers the notification
    void setPrice(float newPrice) {
        this->price = newPrice;
        cout << "\n--- Stock Price changed to $" << price << " ---" << endl;
        notify(); // <--- Automatic Trigger!
    }
};

// --- 4. Concrete Observers ---

class MobileApp : public IObserver {
public:
    void update(float price) override {
        cout << "Mobile App: Push Notification! Price is now $" << price << endl;
    }
};

class Billboard : public IObserver {
public:
    void update(float price) override {
        cout << "Digital Billboard: Updating display to $" << price << endl;
    }
};

// --- 5. The Usage ---
int main() {
    StockMarket* googleStock = new StockMarket();

    MobileApp* myPhone = new MobileApp();
    Billboard* timesSquare = new Billboard();

    // 1. Subscribe
    googleStock->attach(myPhone);
    googleStock->attach(timesSquare);

    // 2. Event Happens
    googleStock->setPrice(150.00);
    // Output: Both get notified

    // 3. Unsubscribe
    cout << "\n(Mobile App unsubscribes...)" << endl;
    googleStock->detach(myPhone);

    // 4. Event Happens Again
    googleStock->setPrice(155.50);
    // Output: Only Billboard gets notified

    delete googleStock;
    delete myPhone;
    delete timesSquare;
    return 0;
}