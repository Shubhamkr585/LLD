#include <iostream>
#include <string>
using namespace std;

// ==========================================
// 1. The Subject Interface
// Both Real and Proxy must look like a "Server".
// ==========================================
class IServer {
public:
    virtual void executeCommand(string command, string userRole) = 0;
    virtual ~IServer() {}
};

// ==========================================
// 2. The Real Subject
// This does the actual dangerous work.
// ==========================================
class RealServer : public IServer {
public:
    void executeCommand(string command, string userRole) override {
        // In real life, this might format a hard drive or reboot a system.
        cout << "RealServer: Executing command '" << command << "'" << endl;
    }
};

// ==========================================
// 3. The Proxy (The Gatekeeper)
// ==========================================
class ProxyServer : public IServer {
private:
    RealServer* realServer; // The Proxy holds a link to the real thing

public:
    ProxyServer() {
        realServer = new RealServer();
    }

    ~ProxyServer() {
        delete realServer;
    }

    void executeCommand(string command, string userRole) override {
        // 1. Access Control Logic (The "Proxy" part)
        if (userRole != "ADMIN") {
            cout << "Proxy: Access Denied! User '" << userRole << "' cannot execute '" << command << "'." << endl;
            return;
        }

        // 2. Logging Logic (Optional Proxy feature)
        cout << " Proxy: Logging request from ADMIN." << endl;

        // 3. Delegate to Real Subject
        realServer->executeCommand(command, userRole);
    }
};

// ==========================================
// 4. The Client
// ==========================================
int main() {
    // The client thinks it's talking to a normal server.
    IServer* server = new ProxyServer();

    // Scenario 1: Basic User tries to delete database
    cout << "--- Attempt 1: Guest User ---" << endl;
    server->executeCommand("DELETE_DB", "GUEST");

    // Scenario 2: Manager tries to delete database
    cout << "\n--- Attempt 2: Manager User ---" << endl;
    server->executeCommand("DELETE_DB", "MANAGER");

    // Scenario 3: Admin tries to delete database
    cout << "\n--- Attempt 3: Admin User ---" << endl;
    server->executeCommand("DELETE_DB", "ADMIN");

    delete server;
    return 0;
}