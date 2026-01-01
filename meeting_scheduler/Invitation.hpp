#pragma once
// Design Pattern: Simple Data Holder (could be part of Observer if extended)
#include <memory>
#include "User.hpp"

class Invitation {
public:
    enum Status { Pending, Accepted, Declined };
private:
    std::shared_ptr<User> invitee;
    Status status;
public:
    Invitation(std::shared_ptr<User> invitee);
    std::shared_ptr<User> getInvitee() const;
    Status getStatus() const;
    void setStatus(Status s);
};
