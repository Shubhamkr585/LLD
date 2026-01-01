#pragma once
#include "elevator.hpp"
#include "elevator_mgr.hpp"
#include "internal_requests_processor.hpp"
#include "external_requests_processor.hpp"
#include "elevator_selection_strategy.hpp"
#include "elevator_control_strategy.hpp"

//Facade
class ElevatorSystem {
    ElevatorSystem() {}
    static ElevatorSystem* elevatorSystemInstance;
    int noOfFloors;
    int noOfElevators;
    ExternalRequestsProcessor* extReqProcessor;
    InternalRequestsProcessor* intReqProcessor;

    public:
        static ElevatorSystem* getElevatorSystem();
        void InitialiseElevatorSystem(int noOfFloors, int noOfElevators);
        void setElevatorSelectionStrategy(ElevatorSelectionStrategy* selectionStrategy);
        void setElevatorControlStrategy(ElevatorControlStrategy* controlStrategy, int elevatorId);
        void sendExternalRequest(ELEVATOR_DIRECTION direction, int srcFloor);
        void sendInternalRequest(int destFloor, int srcElevatorId);
        void step();
        Elevator* getElevator(int elevatorId);
};  