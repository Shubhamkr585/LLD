#pragma once
// Design Pattern: Composite (Meeting contains multiple Invitations)
#include <string>
#include <vector>
#include <memory>
#include "User.hpp"
#include "Room.hpp"
#include "Invitation.hpp"

class Meeting {
    std::string id;
    std::string title;
    std::shared_ptr<User> organizer;
    std::vector<std::shared_ptr<Invitation>> invitations;
    std::shared_ptr<Room> room;
    time_t startTime;
    time_t endTime;
public:
    Meeting(const std::string& id, const std::string& title, std::shared_ptr<User> organizer,
            time_t startTime, time_t endTime, std::shared_ptr<Room> room = nullptr);
    std::string getId() const;
    std::string getTitle() const;
    std::shared_ptr<User> getOrganizer() const;
    std::vector<std::shared_ptr<Invitation>>& getInvitations();
    std::shared_ptr<Room> getRoom() const;
    time_t getStartTime() const;
    time_t getEndTime() const;
};
