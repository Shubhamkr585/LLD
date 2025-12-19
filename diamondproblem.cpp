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




#include <bits/stdc++.h>
using namespace std;


class A {

public:
virtual void show(){
    cout<<"In the class A"<<endl;
}

};

class B: public A {

public:
void show(){
    cout<<"In the class B"<<endl;
}

};

class C: public A {

public:
void show(){
    cout<<"In the class C"<<endl;
}
};

class D:public B,public C{
    public:
    void show(){
        cout<<"In the class D"<<endl;
    }
};

int main(){

C *obj=new D();
obj->show();
return 0;
}