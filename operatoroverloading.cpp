
#include <bits/stdc++.h>
using namespace std;

class Complex{

    int a,b;
    public:
    Complex(){
        this->a=0;
        this->b=0;
        cout<<"Default Constructor called"<<endl;
    }
 Complex(int a,int b){
    this->a=a;
    this->b=b;
    cout<<"Constructor called"<<endl;
 }
 //default copy constructor
 Complex(Complex &c){
    this->a=c.a;
    this->b=c.b;
    cout<<"Copy Constructor called"<<endl;
 }
 Complex operator+(Complex &c){
    
    Complex ans;
    ans.a=this->a+c.a;
    ans.b=this->b+c.b;
    return ans;
 }
 void display(){
    cout<<this->a<<"+"<<this->b<<"i"<<endl;
 }

};
int main() {
Complex c1(1,2);
Complex c2(3,4);
Complex c3(c1);
c2=c2+c1;
c1.display();
c2.display();
c3.display();
// when is the dafault constructor called?
 return 0;
}