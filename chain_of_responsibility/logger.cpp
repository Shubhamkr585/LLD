#include <iostream>
#include <string>
using namespace std;

// 1. The Handler Interface
class LogHandler {
protected:
    LogHandler* nextHandler; // The "Next Guy" in the chain

public:
    LogHandler() : nextHandler(nullptr) {}

    // Setup the chain
    void setNext(LogHandler* next) {
        this->nextHandler = next;
    }

    // The logic to decide: Handle or Pass?
    virtual void handleLog(string level, string message) {
        if (nextHandler) {
            nextHandler->handleLog(level, message);
        } else {
            cout << " No one could handle this log: " << message << endl;
        }
    }
    
    virtual ~LogHandler() {}
};

// 2. Concrete Handlers

// Level 1: Info Handler
class InfoHandler : public LogHandler {
public:
    void handleLog(string level, string message) override {
        if (level == "INFO") {
            cout << "[INFO]: " << message << endl;
        } else {
            // Can't handle it? Pass it on!
            LogHandler::handleLog(level, message);
        }
    }
};

// Level 2: Debug Handler
class DebugHandler : public LogHandler {
public:
    void handleLog(string level, string message) override {
        if (level == "DEBUG") {
            cout << "[DEBUG]: " << message << endl;
        } else {
            LogHandler::handleLog(level, message);
        }
    }
};

// Level 3: Error Handler
class ErrorHandler : public LogHandler {
public:
    void handleLog(string level, string message) override {
        if (level == "ERROR") {
            cout << "[ERROR]: " << message << " (Sent to Admin!)" << endl;
        } else {
            LogHandler::handleLog(level, message);
        }
    }
};

// 3. The Client
int main() {
    // 1. Create the handlers
    LogHandler* info = new InfoHandler();
    LogHandler* debug = new DebugHandler();
    LogHandler* error = new ErrorHandler();

    // 2. Chain them together
    // Chain: Info -> Debug -> Error -> NULL
    info->setNext(debug);
    debug->setNext(error);

    // 3. Send requests to the FIRST link in the chain
    cout << "--- Sending INFO ---" << endl;
    info->handleLog("INFO", "System started");

    cout << "\n--- Sending ERROR ---" << endl;
    // Client asks 'info', but 'info' passes it all the way to 'error'
    info->handleLog("ERROR", "Database Connection Failed!"); 

    cout << "\n--- Sending UNKNOWN ---" << endl;
    info->handleLog("CRITICAL", "Server on fire!");

    // Cleanup
    delete info; delete debug; delete error;
    return 0;
}