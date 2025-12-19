#include<bits/stdc++.h>
using namespace std;
class Complex
{

    int x;
    int y;

    public:

    Complex():x(0),y(0){}

    Complex(int x,int y):x(x),y(y){}
    void display()
    {
        cout<<x<<" "<<y<<endl;
    }

    friend void dost(Complex &c);
};

void dost(Complex &c){
    c.x++;
    c.y++;
}
int main()
{
Complex c1(10,20);
c1.display();
dost(c1);
c1.display();
return 0;
}