#pragma once
#include <iostream>

using namespace std;

enum class ELEVATOR_DIRECTION {
	UP,
	DOWN,
    IDLE
};

enum class ELEVATOR_STATUS {
	IDLE,
    MOVING,
    STOPPED,
};

inline ostream& operator<<(ostream& os, ELEVATOR_DIRECTION dir) {
    switch (dir) {
        case ELEVATOR_DIRECTION::IDLE:
            os << "IDLE";
            break;
        case ELEVATOR_DIRECTION::UP:
            os << "UP";
            break;
        case ELEVATOR_DIRECTION::DOWN:
            os << "DOWN";
            break;
    }
    return os;
}

inline ostream& operator<<(ostream& os, ELEVATOR_STATUS status) {
    switch (status) {
        case ELEVATOR_STATUS::IDLE:
            os << "IDLE";
            break;
        case ELEVATOR_STATUS::MOVING:
            os << "MOVING";
            break;
        case ELEVATOR_STATUS::STOPPED:
            os << "STOPPED";
            break;
    }
    return os;
}
