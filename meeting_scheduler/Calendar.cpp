#include "Calendar.hpp"

void Calendar::addMeeting(const std::shared_ptr<Meeting>& meeting) {
    meetings.push_back(meeting);
}

void Calendar::removeMeeting(const std::string& meetingId) {
    meetings.erase(std::remove_if(meetings.begin(), meetings.end(),
        [&](const std::shared_ptr<Meeting>& m) { return m->getId() == meetingId; }), meetings.end());
}

std::vector<std::shared_ptr<Meeting>> Calendar::getMeetings() const {
    return meetings;
}

std::vector<std::shared_ptr<Meeting>> Calendar::getMeetingsOnDay(time_t dayStart, time_t dayEnd) const {
    std::vector<std::shared_ptr<Meeting>> result;
    for (const auto& m : meetings) {
        if (m->getStartTime() >= dayStart && m->getStartTime() < dayEnd)
            result.push_back(m);
    }
    return result;
}
