#include "User.hpp"
#include <functional>

static std::string simpleHash(const std::string& s) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(s));
}

User::User(const std::string& id, const std::string& name, const std::string& password)
    : id(id), name(name), passwordHash(simpleHash(password)), calendar(std::make_shared<Calendar>()) {}
std::string User::getId() const { return id; }
std::string User::getName() const { return name; }
bool User::authenticate(const std::string& password) const {
    return passwordHash == simpleHash(password);
}
std::shared_ptr<Calendar> User::getCalendar() const {
    return calendar;
}
