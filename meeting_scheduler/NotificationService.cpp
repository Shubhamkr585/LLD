#include "NotificationService.hpp"
#include <iostream>

NotificationService::NotificationService() : running(true), worker(&NotificationService::process, this) {}
void NotificationService::sendAsync(const Notification& msg) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.push(msg);
    cv.notify_one();
}
void NotificationService::stop() {
    running = false;
    cv.notify_one();
    if (worker.joinable()) worker.join();
}
void NotificationService::process() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return !queue.empty() || !running; });
        while (!queue.empty()) {
            auto msg = queue.front();
            queue.pop();
            lock.unlock();
            std::cout << "[Notification] " << msg << std::endl;
            lock.lock();
        }
    }
}
