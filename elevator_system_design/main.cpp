#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include<unordered_map>
using namespace std;

#include "elevator_system.hpp"
#include "odd_even_elevator_sel_strategy.hpp"
#include "zone_elevator_sel_strategy.hpp"
#include "fcfs_ele_ctrl_strat.hpp"
#include "look_algo_ele_ctrl_strat.hpp"
#include "scan_algo_ele_ctrl_strat.hpp"

// Function to print the state of all elevators nicely
void printElevatorStates(ElevatorSystem* elevatorSystem, int numElevators) {
    cout << "\nStatus Update:" << endl;
    for (int i = 1; i <= numElevators; ++i) {
        Elevator* elevator = elevatorSystem->getElevator(i);
        if (elevator) {
            string dirStr = "IDLE";
            if (elevator->getElevatorDirection() == ELEVATOR_DIRECTION::UP) dirStr = "UP  ";
            if (elevator->getElevatorDirection() == ELEVATOR_DIRECTION::DOWN) dirStr = "DOWN";
            
            cout << "  Elevator " << i 
                 << " | Floor: " << elevator->getCurrentFloor() 
                 << " | Dir: " << dirStr << endl;
        }
    }
    cout << "--------------------------------------------------------" << endl;
}

int main() {
    const int NUM_FLOORS = 20;
    const int NUM_ELEVATORS = 2; // Reduced for clearer output
    const int SIMULATION_STEPS = 30;

    // Initialise the Elevator system
    ElevatorSystem* elevatorSystem = ElevatorSystem::getElevatorSystem();
    elevatorSystem->InitialiseElevatorSystem(NUM_FLOORS, NUM_ELEVATORS);

    std::cout << "Setting Elevator Selection Strategy to OddEven" << std::endl;
    elevatorSystem->setElevatorSelectionStrategy(new OddEvenElevatorSelStrategy);
    
    // Set control strategy (Using LOOK algorithm via Controller implementation)
    for (int i = 1; i <= NUM_ELEVATORS; ++i) {
        elevatorSystem->setElevatorControlStrategy(new LookAlgoElevatorControlStrategy(), i);
    }
    
    // Random generators
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> floor_dist(1, NUM_FLOORS);
    std::uniform_int_distribution<> direction_dist(0, 1);

    cout << "\n=== Starting Elevator Simulation ===\n" << endl;

    // Simulation loop
    for (int step = 1; step <= SIMULATION_STEPS; ++step) {
        std::cout << "Time Step " << step;

        // Generate requests more frequently to demonstrate "LOOK" algorithm picking up multiple
        if (step == 1 || step == 5 || step == 10) {
            int fromFloor = floor_dist(gen);
            ELEVATOR_DIRECTION direction = (direction_dist(gen) == 0) ? ELEVATOR_DIRECTION::UP : ELEVATOR_DIRECTION::DOWN;
            
            // Fix edge cases
            if (fromFloor == NUM_FLOORS) direction = ELEVATOR_DIRECTION::DOWN;
            if (fromFloor == 1) direction = ELEVATOR_DIRECTION::UP;

            std::cout << " >>> New External Request: Floor " << fromFloor << " going " << (direction == ELEVATOR_DIRECTION::UP ? "UP" : "DOWN");
            elevatorSystem->sendExternalRequest(direction, fromFloor);
        }
        
        // Simulate internal button presses (people inside pressing floors)
        if (step == 3 || step == 8) {
            int destFloor = floor_dist(gen);
            int elevId = (step % 2) + 1; // Alternate elevators
            std::cout << " >>> Person inside Elevator " << elevId << " pressed Floor " << destFloor;
            elevatorSystem->sendInternalRequest(destFloor, elevId);
        }
        cout << endl;

        // Advance the state
        elevatorSystem->step();

        // Print state
        printElevatorStates(elevatorSystem, NUM_ELEVATORS);

        // Wait to make it readable
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    std::cout << "\n=== Simulation Finished ===" << std::endl;

    return 0;
}