// meeting_scheduler.cpp
// Implementation of Meeting Scheduler classes
#include "meeting_scheduler.hpp"
#include <iostream>
#include <algorithm>

// Simple hash for demonstration (not secure)
#include <functional>
static std::string simpleHash(const std::string& s) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(s));
}
// User
User::User(const std::string& id, const std::string& name, const std::string& password)
    : id(id), name(name), passwordHash(simpleHash(password)) {}
std::string User::getId() const { return id; }
std::string User::getName() const { return name; }
bool User::authenticate(const std::string& password) const {
    return passwordHash == simpleHash(password);
}

// Room
Room::Room(const std::string& id, const std::string& name, int capacity) : id(id), name(name), capacity(capacity) {}
std::string Room::getId() const { return id; }
std::string Room::getName() const { return name; }
int Room::getCapacity() const { return capacity; }

// Invitation
Invitation::Invitation(std::shared_ptr<User> invitee) : invitee(invitee), status(Pending) {}
std::shared_ptr<User> Invitation::getInvitee() const { return invitee; }
Invitation::Status Invitation::getStatus() const { return status; }
void Invitation::setStatus(Status s) { status = s; }

// Meeting
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

// NotificationService (async)
NotificationService::NotificationService() : running(true), worker(&NotificationService::process, this) {}
void NotificationService::sendAsync(const Notification& msg) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.push(msg);
    cv.notify_one();
}
void NotificationService::stop() {
    running = false;
    cv.notify_one();
    if (worker.joinable()) worker.join();
}
void NotificationService::process() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return !queue.empty() || !running; });
        while (!queue.empty()) {
            auto msg = queue.front();
            queue.pop();
            lock.unlock();
            std::cout << "[Notification] " << msg << std::endl;
            lock.lock();
        }
    }
}

// UndoManager
void UndoManager::addAction(const UndoAction& action) {
    std::lock_guard<std::mutex> lock(mtx);
    undoStack.push(action);
    while (!redoStack.empty()) redoStack.pop();
}
void UndoManager::undo() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!undoStack.empty()) {
        auto action = undoStack.top();
        undoStack.pop();
        action();
        redoStack.push(action);
    }
}
void UndoManager::redo() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!redoStack.empty()) {
        auto action = redoStack.top();
        redoStack.pop();
        action();
        undoStack.push(action);
    }
}
bool UndoManager::canUndo() const { return !undoStack.empty(); }
bool UndoManager::canRedo() const { return !redoStack.empty(); }

// MeetingManager
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
// Automatic room assignment based on capacity and availability
std::shared_ptr<Meeting> MeetingManager::scheduleMeeting(const std::string& title, std::shared_ptr<User> organizer,
    time_t startTime, time_t endTime, int requiredCapacity,
    const std::vector<std::shared_ptr<User>>& invitees) {
    std::lock_guard<std::mutex> lock(mtx);
    if (hasConflict(organizer, startTime, endTime)) return nullptr;
    for (auto& user : invitees) {
        if (hasConflict(user, startTime, endTime)) return nullptr;
    }
    // Find available room
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
    return nullptr; // No available room
}
// Schedule meeting with specific room
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
