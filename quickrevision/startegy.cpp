// Strategy
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() = default;
};

// Concrete Strategies
class UPI : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "Paid " << amount << " using UPI\n";
    }
};

class CreditCard : public PaymentStrategy {
public:
    void pay(int amount) override {
        cout << "Paid " << amount << " using Credit Card\n";
    }
};

// Context
class PaymentService {
private:
    PaymentStrategy* strategy;

public:
    PaymentService(PaymentStrategy* strategy)
        : strategy(strategy) {}

    void makePayment(int amount) {
        strategy->pay(amount);
    }
};

int main() {
    UPI upi;
    CreditCard card;

    PaymentService service(&upi);
    service.makePayment(100);

    // Change strategy at runtime
    PaymentService service2(&card);
    service2.makePayment(500);
}

// Strategy Pattern defines a family of interchangeable algorithms, 
// encapsulates each one in a separate class,
//  and allows the client to select or change the algorithm at runtime.


// Observer
class Observer {
public:
    virtual void update(int value) = 0;
    virtual ~Observer() = default;
};

// Concrete Observers
class User : public Observer {
private:
    int id;

public:
    User(int id) : id(id) {}

    void update(int value) override {
        cout << "User " << id << " got update: " << value << endl;
    }
};

// Subject
class Subject {
private:
    vector<Observer*> observers;
    int value = 0;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void setValue(int value) {
        this->value = value;

        for (auto observer : observers)
            observer->update(value);
    }
};

int main() {
    Subject subject;

    User u1(1);
    User u2(2);

    subject.addObserver(&u1);
    subject.addObserver(&u2);

    subject.setValue(100);
}


// state design 


class OrderState {
public:
    virtual void next() = 0;
    virtual void printState() = 0;
    virtual ~OrderState() = default;
};

class PendingState : public OrderState {
public:
    void next() override {
        cout << "Moving to Paid\n";
    }

    void printState() override {
        cout << "Order is Pending\n";
    }
};

class PaidState : public OrderState {
public:
    void next() override {
        cout << "Moving to Shipped\n";
    }

    void printState() override {
        cout << "Order is Paid\n";
    }
};

class Order {
private:
    OrderState* state;

public:
    Order(OrderState* state) : state(state) {}

    void setState(OrderState* state) {
        this->state = state;
    }

    void next() {
        state->next();
    }

    void printState() {
        state->printState();
    }
};

int main() {
    PendingState pending;
    PaidState paid;

    Order order(&pending);

    order.printState();

    order.setState(&paid);

    order.printState();
}

// command design 
#include <iostream>
using namespace std;

// Receiver
class Light {
public:
    void turnOn() {
        cout << "Light ON\n";
    }

    void turnOff() {
        cout << "Light OFF\n";
    }
};

// Command
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

// Concrete Commands
class TurnOnCommand : public Command {
private:
    Light* light;

public:
    TurnOnCommand(Light* light) : light(light) {}

    void execute() override {
        light->turnOn();
    }
};

class TurnOffCommand : public Command {
private:
    Light* light;

public:
    TurnOffCommand(Light* light) : light(light) {}

    void execute() override {
        light->turnOff();
    }
};

// Invoker
class Remote {
private:
    Command* command;

public:
    Remote(Command* command) : command(command) {}

    void pressButton() {
        command->execute();
    }
};

int main() {
    Light light;

    TurnOnCommand on(&light);

    Remote remote(&on);
    remote.pressButton();
}
/*
Client
  |
  v
ConcreteCommand
  |
  v
Receiver
And:

Remote = Invoker
Command = interface
TurnOnCommand = Concrete Command
Light = Receiver
*/
