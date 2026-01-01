#pragma once
// Design Pattern: Facade (provides a simplified interface to user's meetings)
#include <vector>
#include <memory>
#include "Meeting.hpp"

class Calendar {
    std::vector<std::shared_ptr<Meeting>> meetings;
public:
    void addMeeting(const std::shared_ptr<Meeting>& meeting);
    void removeMeeting(const std::string& meetingId);
    std::vector<std::shared_ptr<Meeting>> getMeetings() const;
    std::vector<std::shared_ptr<Meeting>> getMeetingsOnDay(time_t dayStart, time_t dayEnd) const;
};
