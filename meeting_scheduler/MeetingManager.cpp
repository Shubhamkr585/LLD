#include "MeetingManager.hpp"
#include "User.hpp"
#include "Room.hpp"
#include "Meeting.hpp"
#include "Invitation.hpp"

MeetingManager::MeetingManager() {}
std::shared_ptr<User> MeetingManager::registerUser(const std::string& id, const std::string& name, const std::string& password) {
    std::lock_guard<std::mutex> lock(mtx);
    if (users.count(id)) return nullptr;
    auto user = std::make_shared<User>(id, name, password);
    users[id] = user;
    return user;
}
std::shared_ptr<User> MeetingManager::authenticateUser(const std::string& id, const std::string& password) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!users.count(id)) return nullptr;
    auto user = users[id];
    if (user->authenticate(password)) return user;
    return nullptr;
}
std::shared_ptr<Room> MeetingManager::addRoom(const std::string& id, const std::string& name, int capacity) {
    std::lock_guard<std::mutex> lock(mtx);
    if (rooms.count(id)) return nullptr;
    auto room = std::make_shared<Room>(id, name, capacity);
    rooms[id] = room;
    return room;
}
std::vector<std::shared_ptr<Room>> MeetingManager::getRooms() const {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<std::shared_ptr<Room>> result;
    for (const auto& [id, room] : rooms) result.push_back(room);
    return result;
}
std::shared_ptr<Meeting> MeetingManager::scheduleMeeting(const std::string& title, std::shared_ptr<User> organizer,
    time_t startTime, time_t endTime, int requiredCapacity,
    const std::vector<std::shared_ptr<User>>& invitees) {
    std::lock_guard<std::mutex> lock(mtx);
    if (hasConflict(organizer, startTime, endTime)) return nullptr;
    for (auto& user : invitees) {
        if (hasConflict(user, startTime, endTime)) return nullptr;
    }
    for (auto& [id, room] : rooms) {
        if (room->getCapacity() >= requiredCapacity && isRoomAvailable(room, startTime, endTime)) {
            std::string mid = "meeting_" + std::to_string(meetings.size() + 1);
            auto meeting = std::make_shared<Meeting>(mid, title, organizer, startTime, endTime, room);
            for (auto& user : invitees) {
                meeting->getInvitations().push_back(std::make_shared<Invitation>(user));
            }
            meetings[mid] = meeting;
            return meeting;
        }
    }
    return nullptr;
}
std::shared_ptr<Meeting> MeetingManager::scheduleMeetingWithRoom(const std::string& title, std::shared_ptr<User> organizer,
    time_t startTime, time_t endTime, std::shared_ptr<Room> room,
    const std::vector<std::shared_ptr<User>>& invitees) {
    std::lock_guard<std::mutex> lock(mtx);
    if (hasConflict(organizer, startTime, endTime)) return nullptr;
    for (auto& user : invitees) {
        if (hasConflict(user, startTime, endTime)) return nullptr;
    }
    if (!isRoomAvailable(room, startTime, endTime)) return nullptr;
    std::string mid = "meeting_" + std::to_string(meetings.size() + 1);
    auto meeting = std::make_shared<Meeting>(mid, title, organizer, startTime, endTime, room);
    for (auto& user : invitees) {
        meeting->getInvitations().push_back(std::make_shared<Invitation>(user));
    }
    meetings[mid] = meeting;
    return meeting;
}
void MeetingManager::cancelMeeting(const std::string& meetingId) {
    std::lock_guard<std::mutex> lock(mtx);
    meetings.erase(meetingId);
}
std::vector<std::shared_ptr<Meeting>> MeetingManager::getMeetingsForUser(const std::string& userId) {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<std::shared_ptr<Meeting>> result;
    for (auto& [id, meeting] : meetings) {
        if (meeting->getOrganizer()->getId() == userId) result.push_back(meeting);
        else {
            for (auto& inv : meeting->getInvitations()) {
                if (inv->getInvitee()->getId() == userId) {
                    result.push_back(meeting);
                    break;
                }
            }
        }
    }
    return result;
}
std::vector<std::shared_ptr<Meeting>> MeetingManager::getPastMeetingsForUser(const std::string& userId, time_t now) const {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<std::shared_ptr<Meeting>> result;
    for (const auto& [id, meeting] : meetings) {
        if (meeting->getEndTime() < now) {
            if (meeting->getOrganizer()->getId() == userId) result.push_back(meeting);
            else {
                for (auto& inv : meeting->getInvitations()) {
                    if (inv->getInvitee()->getId() == userId) {
                        result.push_back(meeting);
                        break;
                    }
                }
            }
        }
    }
    return result;
}
bool MeetingManager::hasConflict(std::shared_ptr<User> user, time_t startTime, time_t endTime) const {
    for (const auto& [id, meeting] : meetings) {
        if (meeting->getOrganizer()->getId() == user->getId()) {
            if (!(endTime <= meeting->getStartTime() || startTime >= meeting->getEndTime()))
                return true;
        }
        for (auto& inv : meeting->getInvitations()) {
            if (inv->getInvitee()->getId() == user->getId()) {
                if (!(endTime <= meeting->getStartTime() || startTime >= meeting->getEndTime()))
                    return true;
            }
        }
    }
    return false;
}
bool MeetingManager::isRoomAvailable(std::shared_ptr<Room> room, time_t startTime, time_t endTime) const {
    for (const auto& [id, meeting] : meetings) {
        if (meeting->getRoom() && meeting->getRoom()->getId() == room->getId()) {
            if (!(endTime <= meeting->getStartTime() || startTime >= meeting->getEndTime()))
                return false;
        }
    }
    return true;
}
