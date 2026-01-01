#pragma once
#include "internal_display.hpp"
#include "elevator_controller.hpp"

class Elevator {
        int elevatorId; //can be string
        int capacity;   //Can store variables like speed, door open and close time
        vector<InternalDisplay*> displays;
        ElevatorController* controller;
    public:
        Elevator() {
            controller = new ElevatorController();
        }
        int getElevatorId() {
            return elevatorId;
        } 
        ElevatorController* getController() {
            return controller;
        }
        void moveToFloor(int floorNum) {
            controller->moveElevatorToFloor(floorNum);
        }
        void notifyFloorNumUpdate(int floorNum) {
            controller->setCurrFloor(floorNum);
        }

        // New methods for simulation
        void step() {
            controller->step();
        }
        int getCurrentFloor() {
            return controller->getCurrFloor();
        }
        ELEVATOR_DIRECTION getElevatorDirection() {
            return controller->getElevatorDirection();
        }
        ELEVATOR_STATUS getElevatorState() {
            return controller->getElevatorState();
        }
};