#ifndef COLLECTION_INTERFACE_HPP
#define COLLECTION_INTERFACE_HPP

#include "iterator_interface.hpp"

// interface
class ICollection {
public:
    virtual IIterator* createIterator() = 0;
    virtual void addNotification(string val) = 0;
    virtual ~ICollection() {}
};

#endif