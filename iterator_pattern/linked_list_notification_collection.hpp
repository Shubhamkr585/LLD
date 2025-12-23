#pragma once 

#include "collection_interface.hpp"
#include "iterator_interface.hpp"
#include <string>
using namespace std;


// The Concrete Collection for Linked List
class LinkedListCollection : public ICollection {
private:
    // Nested Node structure: Enforces Composition and Encapsulation
    struct Node {
        string data;
        Node* next;
        Node(string val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;

    // Nested Iterator Class
    class LinkedListIterator : public IIterator {
    private:
        Node* current;
    public:
        LinkedListIterator(Node* head) : current(head) {}

        bool hasNext() override {
            return current != nullptr;
        }

        string next() override {
            if (current) {
                string val = current->data;
                current = current->next;
                return val;
            }
            return "";
        }
    };

public:
    LinkedListCollection() : head(nullptr), tail(nullptr) {}

    ~LinkedListCollection() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void addNotification(string val) override{
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Factory Method: Returns the specific iterator for Lists
    IIterator* createIterator() override {
        return new LinkedListIterator(head);
    }
};