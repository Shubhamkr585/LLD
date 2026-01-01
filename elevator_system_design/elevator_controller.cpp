#include "elevator_controller.hpp"

void ElevatorController::addStop(int floor) {
    destinations.insert(floor);
}

void ElevatorController::moveElevatorToFloor(int floorNum) {
    // Determine the next effective stop using the strategy
    // In this design, the strategy validates or transforms the request
    int nextStop = controlStrategy->determineNextStop(floorNum);
    
    // Add the determined stop to our set of destinations
    addStop(nextStop);

    // If we were IDLE, we need to start moving
    if (state->getCurrStatus() == ELEVATOR_STATUS::IDLE) {
        state->setCurrStatus(ELEVATOR_STATUS::MOVING);
        if (nextStop > state->getCurrFloor()) {
            state->setCurrDirection(ELEVATOR_DIRECTION::UP);
        } else {
            state->setCurrDirection(ELEVATOR_DIRECTION::DOWN);
        }
    }
}

void ElevatorController::step() {
    // 1. If no destinations, go IDLE
    if (destinations.empty()) {
        state->setCurrStatus(ELEVATOR_STATUS::IDLE);
        state->setCurrDirection(ELEVATOR_DIRECTION::IDLE);
        return;
    }

    // 2. Determine Direction (LOOK Algorithm Logic)
    int currFloor = state->getCurrFloor();
    ELEVATOR_DIRECTION currDir = state->getCurrDirection();

    bool reqAbove = false;
    bool reqBelow = false;

    for (int floor : destinations) {
        if (floor > currFloor) reqAbove = true;
        if (floor < currFloor) reqBelow = true;
    }

    // If we are IDLE or directionless, pick a direction
    if (currDir == ELEVATOR_DIRECTION::IDLE) {
        if (reqAbove) state->setCurrDirection(ELEVATOR_DIRECTION::UP);
        else if (reqBelow) state->setCurrDirection(ELEVATOR_DIRECTION::DOWN);
        else {
            // We are likely AT the only destination
             if (destinations.count(currFloor)) {
                // Open doors logic below handles this
             }
        }
    } 
    // If moving UP but no more requests above, switch to DOWN (if requests exist)
    else if (currDir == ELEVATOR_DIRECTION::UP && !reqAbove) {
        if (reqBelow) {
            state->setCurrDirection(ELEVATOR_DIRECTION::DOWN);
        } else {
             // No requests anywhere? (Should remain IDLE next tick)
        }
    }
    // If moving DOWN but no more requests below, switch to UP
    else if (currDir == ELEVATOR_DIRECTION::DOWN && !reqBelow) {
        if (reqAbove) {
            state->setCurrDirection(ELEVATOR_DIRECTION::UP);
        }
    }

    // 3. Move the Elevator
    currDir = state->getCurrDirection(); // Refresh direction
    if (state->getCurrStatus() == ELEVATOR_STATUS::MOVING) {
        if (currDir == ELEVATOR_DIRECTION::UP) {
            state->setCurrFloor(currFloor + 1);
        } else if (currDir == ELEVATOR_DIRECTION::DOWN) {
            state->setCurrFloor(currFloor - 1);
        }
    }

    // 4. Check if we reached a stop
    int newFloor = state->getCurrFloor();
    if (destinations.count(newFloor)) {
        cout << "   [ELEVATOR STOP] Reached Floor " << newFloor << ". Doors Opening..." << endl;
        destinations.erase(newFloor);
        // In a real system, we would wait here. 
        // For simulation, we assume instantaneous unload/load for simplicity, 
        // or we could pause the state machine for a tick.
    }
}