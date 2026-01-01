// Meeting Scheduler - Main Classes and Responsibilities
// Thread-safe, async, in-memory, full undo/cancel history
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <stack>
#include <atomic>

class User;
class Meeting;
class Room;
class Invitation;
class NotificationService;
class MeetingManager;
class UndoManager;

// User entity
class User {
    std::string id;
    std::string name;
    std::string passwordHash;
public:
    User(const std::string& id, const std::string& name, const std::string& password);
    std::string getId() const;
    std::string getName() const;
    bool authenticate(const std::string& password) const;
};

// Room entity
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

// Invitation entity
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

// Meeting entity
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

// NotificationService (async)
class NotificationService {
public:
    using Notification = std::string;
    NotificationService();
    void sendAsync(const Notification& msg);
    void stop();
private:
    std::queue<Notification> queue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread worker;
    std::atomic<bool> running;
    void process();
};

// UndoManager with full history
class UndoManager {
public:
    using UndoAction = std::function<void()>;
    void addAction(const UndoAction& action);
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;
private:
    std::stack<UndoAction> undoStack;
    std::stack<UndoAction> redoStack;
    std::mutex mtx;
};

// MeetingManager (thread-safe)
class MeetingManager {
public:
    MeetingManager();
    // Register and authenticate users
    std::shared_ptr<User> registerUser(const std::string& id, const std::string& name, const std::string& password);
    std::shared_ptr<User> authenticateUser(const std::string& id, const std::string& password);
    // Room management
    std::shared_ptr<Room> addRoom(const std::string& id, const std::string& name, int capacity);
    std::vector<std::shared_ptr<Room>> getRooms() const;
    // Schedule meeting with automatic room assignment
    std::shared_ptr<Meeting> scheduleMeeting(const std::string& title, std::shared_ptr<User> organizer,
        time_t startTime, time_t endTime, int requiredCapacity,
        const std::vector<std::shared_ptr<User>>& invitees);
    // Schedule meeting with specific room
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
