// main.cpp
// Demonstration of Meeting Scheduler usage
#include "meeting_scheduler.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    MeetingManager meetingManager;
    NotificationService notificationService;
    UndoManager undoManager;

    // Register users
    auto alice = meetingManager.registerUser("u1", "Alice", "alicepass");
    auto bob = meetingManager.registerUser("u2", "Bob", "bobpass");
    auto carol = meetingManager.registerUser("u3", "Carol", "carolpass");

    // Authenticate users (demo)
    auto aliceAuth = meetingManager.authenticateUser("u1", "alicepass");
    if (!aliceAuth) {
        std::cout << "Authentication failed for Alice!" << std::endl;
        return 1;
    }

    // Add rooms
    auto room1 = meetingManager.addRoom("r1", "Conference Room 1", 5);
    auto room2 = meetingManager.addRoom("r2", "Small Room", 2);

    // Schedule a meeting (auto room assignment)
    time_t now = time(nullptr);
    std::vector<std::shared_ptr<User>> participants = {bob, carol};
    int requiredCapacity = 1 + (int)participants.size();
    auto meeting = meetingManager.scheduleMeeting(
        "Project Kickoff", alice, now + 60, now + 3600, requiredCapacity, participants);
    if (meeting) {
        notificationService.sendAsync("[Email/SMS] Meeting scheduled: " + meeting->getTitle() + " in room: " + meeting->getRoom()->getName());
        // Add undo action
        undoManager.addAction([&meetingManager, id = meeting->getId()]() {
            meetingManager.cancelMeeting(id);
            std::cout << "[Undo] Meeting " << id << " cancelled." << std::endl;
        });
    } else {
        std::cout << "Failed to schedule meeting due to conflict or no available room." << std::endl;
    }

    // Calendar view for Alice
    auto meetingsForAlice = meetingManager.getMeetingsForUser(alice->getId());
    std::cout << "\nAlice's Calendar:" << std::endl;
    for (const auto& m : meetingsForAlice) {
        std::cout << "- " << m->getTitle() << " in room: " << (m->getRoom() ? m->getRoom()->getName() : "N/A") << std::endl;
    }

    // Cancel the meeting (undo)
    if (undoManager.canUndo()) {
        undoManager.undo();
        notificationService.sendAsync("[Email/SMS] Meeting undo/cancelled.");
    }

    // Redo the meeting
    if (undoManager.canRedo()) {
        undoManager.redo();
        notificationService.sendAsync("[Email/SMS] Meeting re-scheduled (redo).");
    }

    // Show past meetings (simulate time passing)
    auto pastMeetings = meetingManager.getPastMeetingsForUser(alice->getId(), now + 7200);
    std::cout << "\nAlice's Past Meetings:" << std::endl;
    for (const auto& m : pastMeetings) {
        std::cout << "- " << m->getTitle() << " (ended at " << m->getEndTime() << ")" << std::endl;
    }

    // Wait for async notifications to print
    std::this_thread::sleep_for(std::chrono::seconds(1));
    notificationService.stop();
    return 0;
}
