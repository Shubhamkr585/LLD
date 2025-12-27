#include <iostream>
#include "linked_list_notification_collection.hpp"
#include "notification_collection.hpp"


using namespace std;

int main() {
    // 1. Create Collection
    ICollection* inbox = new LinkedListCollection();
    inbox->addNotification("Your order shipped");
    inbox->addNotification("New friend request");
    inbox->addNotification("Update available");

    // 2. Create an iterator
    IIterator* iterator = inbox->createIterator();

    // 3. Traverse the collection using the iterator
    cout << "Traversing notifications:" << endl;
    while (iterator->hasNext()) {
        cout << iterator->next() << endl;
    }

    // 4. Demonstrate that a new iterator starts from the beginning
    cout << "\nStarting a new traversal with a second iterator:" << endl;
    IIterator* iterator2 = inbox->createIterator();
    while (iterator2->hasNext()) {
        cout << iterator2->next() << endl;
    }

    // craete a new colletion storing data in the form of vector
    ICollection* notifications = new NotificationCollection();
    notifications->addNotification("Happy New Year");
    notifications->addNotification("Enjoy the day");
    notifications->addNotification("Wish you all the best");
    IIterator* iterator3 = notifications->createIterator();

    cout << "Traversing notifications:" << endl;
    while (iterator3->hasNext()) {
        cout << iterator3->next() << endl;
    }



    // Clean up
    delete iterator;
    delete iterator2;
    delete iterator3;
    delete inbox;
    delete notifications;



    return 0;
}