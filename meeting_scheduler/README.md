# Meeting Scheduler LLD Project

## Files
- meeting_scheduler.hpp: Class definitions for User, Meeting, Room, Invitation, NotificationService, MeetingManager, UndoManager
- meeting_scheduler.cpp: Implementation of all classes
- main.cpp: Demonstration of scheduling, async notification, undo/cancel

## Features
- In-memory, thread-safe, async notification, full undo/cancel history
- Demonstrates OOP, concurrency, and extensibility

## How to Build

```
g++ -std=c++17 -pthread main.cpp meeting_scheduler.cpp -o meeting_scheduler
```

## How to Run

```
./meeting_scheduler
```

## Main Concepts
- Thread safety: mutexes in shared classes
- Async notification: queue + worker thread
- Undo/redo: full action history
- Internal class interactions only (no external API)
