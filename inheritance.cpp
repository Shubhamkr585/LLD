#include<bits/stdc++.h>
using namespace std;

// class A {
// public:
//     virtual void show() { cout << "A\n"; }
// };

// class B : public A {
// public:
//     void show() { cout << "B\n"; }
// };

// int main(){
//     A *ptr=new B();
//     ptr->show();
//     return 0;
// }


class A {
public:
    virtual void show() { cout << "A\n"; }
    virtual ~A(){
        cout<<"Then the destructor of base class is called"<<endl;
    }
};

class B :public A {
public:
// note if this class misses its implementation then the function of the 
// base class will be called
// however if the base class function is pure virtual then it will throw error
    void show() { cout << "B\n"; }
    ~B(){
        cout<<"First the destructor of child class is called"<<endl;
    }
};

int main(){
    A *ptr=new B();
    ptr->show();
    delete ptr;
    return 0;
}



