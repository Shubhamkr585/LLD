#include <bits/stdc++.h>
using namespace std;

class DatabaseConnection {
private:
    // Private constructor to prevent direct creation
    DatabaseConnection() {
        cout << "Database Connection Created (Heavy Operation)" << endl;
    }

    // The single instance is declared here
    static DatabaseConnection instance;

public:
    // We just return the pre-existing instance
    static DatabaseConnection& getInstance() {
        return instance;
    }
    
    void query(string q) { cout << "Executing: " << q << endl; }
};

// INITIALIZATION happens here, before main() starts!
DatabaseConnection DatabaseConnection::instance; 

int main() {
    cout << "App Started" << endl;
    // The object already exists in memory right now.
    
    // Usage
    DatabaseConnection::getInstance().query("SELECT * FROM users");
}