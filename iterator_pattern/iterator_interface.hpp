#ifndef ITERATOR_INTERFACE_HPP
#define ITERATOR_INTERFACE_HPP

#include <string>
#include <iostream>
using namespace std;

// interface 
class IIterator {
public:
    virtual bool hasNext() = 0;
    virtual string next() = 0;
    virtual ~IIterator() {}
};

#endif