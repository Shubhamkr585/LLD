#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex> 


using namespace std;

class DatabaseConnection {
private:
    // 1. The static pointer
    static DatabaseConnection* instance;
    
    // Private constructor (we add a print here to see when it runs)
    DatabaseConnection() {
        cout << "CRITICAL FAILURE: A new DatabaseConnection object was created! at address: " << this << endl;
    }

public:
    // 2. The Broken Lazy Initialization (No Mutex)
    static DatabaseConnection* getInstance() {
        if (instance == nullptr) {
            
            // We force this thread to sleep for 100ms right here.
            // This simulates the OS switching context to another thread 
            // at the worst possible moment.
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            // In a race condition, multiple threads reach this line
            // because they all passed the "if (instance == nullptr)" check
            // while the first one was sleeping/working.
            instance = new DatabaseConnection();
        }
        return instance;
    }
};

// Initialize static member
DatabaseConnection* DatabaseConnection::instance = nullptr;

// A simple function for threads to run
void threadTask() {
    DatabaseConnection* db = DatabaseConnection::getInstance();
}

int main() {
    cout << "--- Starting Race Condition Simulation ---" << endl;

    vector<thread> threads;

    // Launch 5 threads at arguably the "same time"
    for (int i = 0; i < 5; i++) {
        threads.push_back(thread(threadTask));
    }

    // Wait for all to finish
    for (auto& t : threads) {
        t.join();
    }

    cout << "--- Simulation Finished ---" << endl;
    
    // In a correct Singleton, you should only see the "CRITICAL FAILURE" message ONCE.
    // Here, you will likely see it 5 times.
    return 0;
}



// solution to race conditon

class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    static std::mutex mtx; // 1. The Lock

    DatabaseConnection() {
        cout << " SUCCESS: DatabaseConnection created at: " << this << endl;
    }

public:
    static DatabaseConnection* getInstance() {
        // CHECK 1: Optimization
        // If instance already exists, return it immediately. 
        // No need to lock (locking is slow).
        if (instance == nullptr) {
            
            // 2. Acquire Lock
            // Only ONE thread can pass this line at a time.
            // Others must wait here.
            std::lock_guard<std::mutex> lock(mtx);
            
            // CHECK 2: Safety
            // We check AGAIN inside the lock.
            // Why? Because while Thread B was waiting for the lock, 
            // Thread A might have just finished creating the instance.
            if (instance == nullptr) {
                
                // Simulate the delay again to prove it works
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                
                instance = new DatabaseConnection();
            }
        }
        return instance;
    }
};

// Initialize static members
DatabaseConnection* DatabaseConnection::instance = nullptr;
std::mutex DatabaseConnection::mtx;

void threadTask(int id) {
    DatabaseConnection* db = DatabaseConnection::getInstance();
    // cout << "Thread " << id << " got instance: " << db << endl;
}

int main() {
    cout << "--- Starting Safe Simulation ---" << endl;

    vector<thread> threads;
    for (int i = 0; i < 5; i++) {
        threads.push_back(thread(threadTask, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "--- Simulation Finished ---" << endl;
    return 0;
}