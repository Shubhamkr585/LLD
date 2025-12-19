#include <bits/stdc++.h>
using namespace std;

class Person {
    public:
        string name;
        int salary;

        Person(): name(""), salary(0) {}
        Person(string name, int salary) {
            this->name = name;
            this->salary = salary;
        }

        Person combinedSalaryOfTwoPersons(Person p1, Person p2) {
            Person p3;
            p3.salary = p1.salary + p2.salary;
            return p3;
        }
};

int main() {
    Person p1("Rohan", 20);
    Person p2("Rahul", 30);
    cout << (p1.combinedSalaryOfTwoPersons(p1, p2)).salary<< endl;
    return 0;
}