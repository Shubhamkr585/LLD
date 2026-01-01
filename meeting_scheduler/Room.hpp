#pragma once
// Design Pattern: Simple Data Holder
#include <string>

class Room {
    std::string id;
    std::string name;
    int capacity;
public:
    Room(const std::string& id, const std::string& name, int capacity);
    std::string getId() const;
    std::string getName() const;
    int getCapacity() const;
};
