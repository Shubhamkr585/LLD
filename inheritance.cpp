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
};

class B :public A {
public:
    void show() { cout << "B\n"; }
};

int main(){
    A *ptr=new B();
    ptr->show();
    return 0;
}



vector<int> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;  

    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i])
            primes.push_back(i);
    }
    return primes;
}