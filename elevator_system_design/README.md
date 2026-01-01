# Elevator System Design

This project is a C++ implementation of an elevator system, designed using common software design patterns to be modular, extensible, and maintainable.

## Design Patterns Used

- **Facade Pattern**: The `ElevatorSystem` class acts as a facade, providing a simple and unified interface to the complex underlying subsystems.
- **Singleton Pattern**: `ElevatorSystem` and `ElevatorMgr` are implemented as singletons to ensure a single, globally accessible instance for each.
- **Strategy Pattern**: 
    - `ElevatorSelectionStrategy`: This pattern is used to select an elevator to service a request. Different strategies can be implemented and switched at runtime (e.g., `OddEvenElevatorSelStrategy`, `ZoneElevatorSelStrategy`).
    - `ElevatorControlStrategy`: This pattern is used to determine the next stop for an elevator. Different strategies can be assigned to each elevator (e.g., `FCFSElevatorControlStrategy`, `ScanElevatorControlStrategy`, `LookElevatorControlStrategy`).

## Core Components

- **`ElevatorSystem`**: The main entry point for the system.
- **`ElevatorMgr`**: Manages the elevators in the system.
- **`Elevator`**: Represents an elevator.
- **`ElevatorController`**: Controls the movement and state of an elevator.
- **Request Processors**: `ExternalRequestsProcessor` and `InternalRequestsProcessor` handle requests from outside and inside the elevators, respectively.
- **Strategies**: Various strategy classes for elevator selection and control.

## How to Compile and Run

The `main.cpp` provides a demonstration of the system.

**Compilation:**
```bash
g++ main.cpp elevator_system.cpp elevator_mgr.cpp -o elevator_system_demo
```

**Execution:**
```bash
./elevator_system_demo
```
