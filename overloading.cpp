#include <bits/stdc++.h>
using namespace std;

class Person {
private:
    static int a;        // Step 1: declaration
    string name;
    long long salary;

public:
    Person(string name, long long salary) {
        this->name = name;
        this->salary = salary;
        a = 10;          // static variable shared across all objects
    }

    double calculateTax(int per) {
        double tax = (1.0 * per / 100) * salary * 2;
        return tax;
    }

    double calculateTax(long long per) {
        double tax = salary * .18;
        cout << a << endl;   // must be before return to execute
        return tax;
    }

    void print() {
        cout << name << " " << salary << endl;
        a++;
        cout << a << endl;
    }
};

// Step 2: definition outside the class
int Person::a = 0;

int main() {
    long long sa = 100;
    short per = 18;

    Person p("Rohan", sa);

    p.print();
    p.print();
    p.print();

    cout << p.calculateTax(per) << endl;

    return 0;
}
