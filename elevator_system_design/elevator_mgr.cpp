#include <bits/stdc++.h>
using namespace std;

#include "elevator_mgr.hpp"

ElevatorMgr *ElevatorMgr::elevatorMgrInstance = nullptr;

ElevatorMgr *ElevatorMgr::getElevatorMgr()
{
    if (elevatorMgrInstance == NULL)
    {
        elevatorMgrInstance = new ElevatorMgr();
    }
    return elevatorMgrInstance;
}

void ElevatorMgr::initialiseElevators(int noOfElevators) {
    for(int ind = 1; ind <= noOfElevators; ind++) {
        elevators[ind] = new Elevator();
    }
}

std::vector<Elevator*> ElevatorMgr::getElevators() {
    std::vector<Elevator*> elevatorList;
    for (auto const& [id, elevator] : elevators) {
        elevatorList.push_back(elevator);
    }
    return elevatorList;
}