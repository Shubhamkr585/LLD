#pragma once
#include "elevator_curr_state.hpp"
#include "elevator_control_strategy.hpp"
#include "fcfs_ele_ctrl_strat.hpp"
#include "look_algo_ele_ctrl_strat.hpp"
#include "scan_algo_ele_ctrl_strat.hpp"
#include "seek_time_ele_ctrl_strat.hpp"

#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Controls movement, fan, light, alarm for elevator
class ElevatorController {
        ElevatorCurrState* state;
        ElevatorControlStrategy* controlStrategy;
        
        // Use a set to keep destinations sorted and unique. 
        // This is crucial for the LOOK algorithm.
        std::set<int> destinations; 

    public:
        ElevatorController() {
            state = new ElevatorCurrState();
            // Setting default control strategy
            controlStrategy = new LookAlgoElevatorControlStrategy();
        }

        ~ElevatorController() {
            delete state;
            delete controlStrategy;
        }

        void step();
        void addStop(int floor);
        int getCurrFloor() { return state->getCurrFloor(); }
        ELEVATOR_DIRECTION getElevatorDirection() { return state->getCurrDirection(); }
        ELEVATOR_STATUS getElevatorState() { return state->getCurrStatus(); }

        void setControlStrategy(ElevatorControlStrategy* strategy) {
            if (controlStrategy) delete controlStrategy;
            controlStrategy = strategy;
        }

        void setCurrFloor(int floorNum) {
            state->setCurrFloor(floorNum);
        }

        void moveElevatorToFloor(int floorNum);
};