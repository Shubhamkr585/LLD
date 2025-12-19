#include <bits/stdc++.h>
using namespace std;

class Complex
{
public:
    int a, b;
    Complex(){
        this->a = 0;
        this->b = 0;
    }
    Complex(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
    Complex(Complex &c)
    {
        this->a = c.a;
        this->b = c.b;
    }
   
};

int main(){
    Complex c1(1,2);
    Complex c2(c1);
    cout<<c2.a<<" "<<c2.b<<endl;
    return 0;
}