#ifndef NOTIFICATION_COLLECTION_HPP
#define NOTIFICATION_COLLECTION_HPP

#include "collection_interface.hpp"
#include "notification_iterator.hpp" // Needs to know about the specific iterator
#include <vector>
#include <string>

class NotificationCollection : public ICollection {
private:
    vector<string> notifications;

public:
   
    void addNotification(string msg) override {
        notifications.push_back(msg);
    }

    // Returns the inner vector (needed by the iterator)
    vector<string>& getData() {
        return notifications;
    }

    // Factory Method implementation
    IIterator* createIterator() override {
        return new NotificationIterator(notifications);
    }
};

#endif