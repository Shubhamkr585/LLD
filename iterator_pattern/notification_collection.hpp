#ifndef NOTIFICATION_COLLECTION_HPP
#define NOTIFICATION_COLLECTION_HPP

#include "collection_interface.hpp"
#include <vector>
#include <string>

class NotificationCollection : public ICollection {
private:
    vector<string> notifications;

    // Nested Iterator Class: Hides implementation details
    class NotificationIterator : public IIterator {
    private:
        vector<string>& collection; // Reference to the private data
        int position;

    public:
        NotificationIterator(vector<string>& data) : collection(data), position(0) {}

        bool hasNext() override {
            return position < collection.size();
        }

        string next() override {
            if (this->hasNext()) {
                return collection[position++];
            }
            return "";
        }
    };

public:
   
    void addNotification(string msg) override {
        notifications.push_back(msg);
    }

    // Factory Method implementation
    IIterator* createIterator() override {
        return new NotificationIterator(notifications);
    }
};

#endif