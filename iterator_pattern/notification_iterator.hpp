#ifndef NOTIFICATION_ITERATOR_HPP
#define NOTIFICATION_ITERATOR_HPP

#include "iterator_interface.hpp"
#include <vector>
#include <string>

class NotificationIterator : public IIterator {
private:
    vector<string>& collection; // Reference to the data
    int position;

public:
    NotificationIterator(vector<string>& data) : collection(data), position(0) {}

    bool hasNext() override {
        // Are we at the end?
        return position < collection.size();
    }

    string next() override {
        // Return current item and move pointer forward
        if (this->hasNext()) {
            return collection[position++];
        }
        return "";
    }
};

#endif
