#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

std::mutex console_mtx; // Prevents scrambled text in the console

void independent_task(int id, int sleep_seconds) {
    // 1. std::this_thread::get_id() - Identify the current thread
    std::thread::id this_id = std::this_thread::get_id();

    {
        std::lock_guard<std::mutex> lock(console_mtx);
        std::cout << "[Thread " << id << "] Started with System ID: " << this_id << std::endl;
    }

    // 2. std::this_thread::sleep_for() - Simulate work independently
    std::this_thread::sleep_for(std::chrono::seconds(sleep_seconds));

    {
        std::lock_guard<std::mutex> lock(console_mtx);
        std::cout << "[Thread " << id << "] Finished work after " << sleep_seconds << "s." << std::endl;
    }
}

int main() {
    std::cout << "Main thread starting. Using " << std::thread::hardware_concurrency() 
              << " hardware threads available on this machine.\n" << std::endl;

    // Creating 4 threads with different behaviors
    std::thread t1(independent_task, 1, 2);
    std::thread t2(independent_task, 2, 1);
    std::thread t3(independent_task, 3, 0);
    std::thread t4([]() { 
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(console_mtx);
        std::cout << "[Thread 4] I am a lambda thread running in the background!" << std::endl;
    });

    // 3. .joinable() - Check if a thread can be joined or detached
    if (t1.joinable()) {
        std::cout << "Thread 1 is joinable. Main will wait for it." << std::endl;
        // 4. .join() - Block main until t1 finishes
        t1.join(); 
    }

    // 5. .detach() - Let t2 run independently (Main won't wait)
    // Warning: Only detach if the thread doesn't access local variables that might go out of scope.
    if (t2.joinable()) {
        std::cout << "Detaching Thread 2... it will finish on its own." << std::endl;
        t2.detach();
    }

    // Wait for the remaining threads to ensure they finish before main exits
    if (t3.joinable()) t3.join();
    if (t4.joinable()) t4.join();

    std::cout << "\nMain thread finished. All joined threads completed." << std::endl;
    return 0;
}
