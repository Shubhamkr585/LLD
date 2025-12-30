// class A { public: int data; };

// // B and C virtually inherit from A
// class B: virtual public A { /* ... */ };
// class C: virtual public A { /* ... */ };

// // D inherits from B and C
// class D: public B, public C { /* ... */ };

// int main() {
//     D my_d_object;
//     my_d_object.data = 10; 
// }




// #include <bits/stdc++.h>
// using namespace std;


// class A {
// public:

// //  A(){
// //     cout<<"In the constructor of class A"<<endl;
// //  }
//   int data;

//   void show(){
//     cout<<"In the class A"<<endl;
// }

// };

// class B:public A {

// public:
// void show(){
//     cout<<"In the class B"<<endl;
// }

// };

// class C:  public A {

// public:
// void show(){
//     cout<<"In the class C"<<endl;
// }
// };

// class D:public B{
//     public:
//     void show(){
//         cout<<"In the class D"<<endl;
//     }
// };

// int main(){

// D obj;
// obj.show();
// obj.B::data = 10;
// // obj.C::data = 20;
// obj.A::show();

// cout << "Data via B: " << obj.B::data << endl; // Prints 10
// // cout << "Data via C: " << obj.C::data << endl; // Prints 20
// return 0;
// }

//DIAMOND PROBLEM


// #include <iostream>
// using namespace std;

// class A {
// public:
//     void show() { cout << "Hello from A" << endl; }
// };

// class B : public A {};
// class C : public A {};

// class D : public B, public C {};

// int main() {
//     D obj;
//     // obj.show(); // ERROR: Request for member 'show' is ambiguous
//     // The compiler doesn't know whether to use B's copy of A or C's copy of A.
//     return 0;
// }


// SOLUTION : VIRTUAL INHERITANCE


#include <iostream>
using namespace std;

class A {
public:
    virtual void show() { cout << "Fixed: Only one copy of A exists!" << endl; }
};

// Use 'virtual' keyword here
class B : virtual public A {};
class C : virtual public A {};

class D : public B, public C {
    
public:
    void show() {
        cout << "Hello from D" << endl;
    }

};

int main() {
    A *obj=new D();
    obj->show(); 
    return 0;
}
