#include "Room.hpp"

Room::Room(const std::string &id, const std::string &name, int capacity)
    : id(id), name(name), capacity(capacity) {}
std::string Room::getId() const { return id; }
std::string Room::getName() const { return name; }
int Room::getCapacity() const { return capacity; }
