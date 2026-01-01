#include <bits/stdc++.h>
using namespace std;

#include "elevator_system.hpp"

ElevatorSystem *ElevatorSystem::elevatorSystemInstance = nullptr;

ElevatorSystem *ElevatorSystem::getElevatorSystem()
{
    if (elevatorSystemInstance == NULL)
    {
        elevatorSystemInstance = new ElevatorSystem();
    }
    return elevatorSystemInstance;
}

void ElevatorSystem::InitialiseElevatorSystem(int pNoOfFloors, int pNoOfElevators) {
    cout<<"Initializing elevator system with "<<pNoOfFloors<<" floors and "<<pNoOfElevators<<" elevators!"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    
    noOfElevators = pNoOfElevators;
    noOfFloors = pNoOfFloors;

    //Initialise Elevator Mgr
    ElevatorMgr* elevatorMgr = ElevatorMgr::getElevatorMgr();
    elevatorMgr->initialiseElevators(noOfElevators);

    //Initialise requests processors
    extReqProcessor = new ExternalRequestsProcessor();
    intReqProcessor = new InternalRequestsProcessor();
    
}

void ElevatorSystem::setElevatorSelectionStrategy(ElevatorSelectionStrategy* selectionStrategy) {
    extReqProcessor->setElevatorSelectionStrategy(selectionStrategy);
}

void ElevatorSystem::sendExternalRequest(ELEVATOR_DIRECTION direction, int srcFloor) {
    extReqProcessor->processExternalRequest(new ExternalRequest(direction, srcFloor));
}

void ElevatorSystem::sendInternalRequest(int destFloor, int srcElevatorId) {
    intReqProcessor->processInternalRequest(new InternalRequest(destFloor, srcElevatorId));
}

void ElevatorSystem::setElevatorControlStrategy(ElevatorControlStrategy* controlStrategy, int elevatorId) {
    ElevatorMgr* elevatorMgr = ElevatorMgr::getElevatorMgr();
    Elevator* elevator = elevatorMgr->getElevator(elevatorId);
    elevator->getController()->setControlStrategy(controlStrategy);
}

Elevator* ElevatorSystem::getElevator(int elevatorId) {
    ElevatorMgr* elevatorMgr = ElevatorMgr::getElevatorMgr();
    return elevatorMgr->getElevator(elevatorId);
}

void ElevatorSystem::step() {
    ElevatorMgr* elevatorMgr = ElevatorMgr::getElevatorMgr();
    for (auto elevator : elevatorMgr->getElevators()) {
        elevator->step();
    }
}