#pragma once
// Design Patterns: Mediator (coordinates Users, Rooms, Meetings, Invitations),
// Thread-Safe (mutex), Singleton (if used as single instance), Command (via UndoManager)
#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex>
#include "User.hpp"
#include "Room.hpp"
#include "Meeting.hpp"

class MeetingManager {
public:
    MeetingManager();
    std::shared_ptr<User> registerUser(const std::string& id, const std::string& name, const std::string& password);
    std::shared_ptr<User> authenticateUser(const std::string& id, const std::string& password);
    std::shared_ptr<Room> addRoom(const std::string& id, const std::string& name, int capacity);
    std::vector<std::shared_ptr<Room>> getRooms() const;
    std::shared_ptr<Meeting> scheduleMeeting(const std::string& title, std::shared_ptr<User> organizer,
        time_t startTime, time_t endTime, int requiredCapacity,
        const std::vector<std::shared_ptr<User>>& invitees);
    std::shared_ptr<Meeting> scheduleMeetingWithRoom(const std::string& title, std::shared_ptr<User> organizer,
        time_t startTime, time_t endTime, std::shared_ptr<Room> room,
        const std::vector<std::shared_ptr<User>>& invitees);
    void cancelMeeting(const std::string& meetingId);
    std::vector<std::shared_ptr<Meeting>> getMeetingsForUser(const std::string& userId);
    bool hasConflict(std::shared_ptr<User> user, time_t startTime, time_t endTime) const;
    bool isRoomAvailable(std::shared_ptr<Room> room, time_t startTime, time_t endTime) const;
    std::vector<std::shared_ptr<Meeting>> getPastMeetingsForUser(const std::string& userId, time_t now) const;
private:
    std::unordered_map<std::string, std::shared_ptr<User>> users;
    std::unordered_map<std::string, std::shared_ptr<Room>> rooms;
    std::unordered_map<std::string, std::shared_ptr<Meeting>> meetings;
    mutable std::mutex mtx;
};
