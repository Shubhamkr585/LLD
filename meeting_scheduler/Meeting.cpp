#include "Meeting.hpp"

Meeting::Meeting(const std::string& id, const std::string& title, std::shared_ptr<User> organizer,
    time_t startTime, time_t endTime, std::shared_ptr<Room> room)
    : id(id), title(title), organizer(organizer), startTime(startTime), endTime(endTime), room(room) {}
std::string Meeting::getId() const { return id; }
std::string Meeting::getTitle() const { return title; }
std::shared_ptr<User> Meeting::getOrganizer() const { return organizer; }
std::vector<std::shared_ptr<Invitation>>& Meeting::getInvitations() { return invitations; }
std::shared_ptr<Room> Meeting::getRoom() const { return room; }
time_t Meeting::getStartTime() const { return startTime; }
time_t Meeting::getEndTime() const { return endTime; }
