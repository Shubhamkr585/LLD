#pragma once
// Design Patterns: Producer-Consumer (async queue), can be extended to Observer (for user subscriptions)
#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>

class NotificationService {
public:
    using Notification = std::string;
    NotificationService();
    void sendAsync(const Notification& msg);
    void stop();
private:
    std::queue<Notification> queue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread worker;
    std::atomic<bool> running;
    void process();
};
