#pragma once
// Design Pattern: Simple Data Holder, Facade (via Calendar)
#include <string>
#include <memory>
#include "Calendar.hpp"

class User {
    std::string id;
    std::string name;
    std::string passwordHash;
    std::shared_ptr<Calendar> calendar;
public:
    User(const std::string& id, const std::string& name, const std::string& password);
    std::string getId() const;
    std::string getName() const;
    bool authenticate(const std::string& password) const;
    std::shared_ptr<Calendar> getCalendar() const;
};
