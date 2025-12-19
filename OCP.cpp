// ✅ GOOD LLD - OCP APPLIED

// 1. The Interface (The "Plug")

#include <bits/stdc++.h>
using namespace std;

class INotification {
public:
    virtual void send(string message) = 0;
    virtual ~INotification() {}
};

// 2. The Extensions (The "Plugins")
class EmailNotification : public INotification {
public:
    void send(string message) override {
        cout << "📧 Sending Email: " << message << endl;
    }
};

class SMSNotification : public INotification {
public:
    void send(string message) override {
        cout << "📱 Sending SMS: " << message << endl;
    }
};

class WhatsAppNotification : public INotification {
public:
    void send(string message) override {
        cout << "💬 Sending WhatsApp: " << message << endl;
    }
};

class PushNotification : public INotification {
public:
    void send(std::string message) override {
        std::cout << "🔔 Sending Push Notification: " << message << std::endl;
    }
};


// 3. The Usage
// This class is now "Closed for Modification". 
// You can add 100 new notification types, and you will NEVER touch this code.
class NotificationService {
public:
    void sendAlert(INotification* channel, string msg) {
        channel->send(msg);
    }
};

int main() {
    try {
        // create notifications of each types and call the NotificationServices
        INotification* email = new EmailNotification();
        INotification* sms = new SMSNotification();
        INotification* whatsapp = new WhatsAppNotification();
        INotification* push = new PushNotification();
        NotificationService* service = new NotificationService();
        if (service == nullptr || email == nullptr || sms == nullptr || whatsapp == nullptr || push == nullptr) {
            throw std::runtime_error("Null pointer reference");
        }
        // here we do not care which particular functionality if the particular class are to be
        //used we just know that the type of service we want to use and message we want to send
        service->sendAlert(email, "kya kar raha h re");
        service->sendAlert(sms, "kya kar raha h re");
        service->sendAlert(whatsapp, "kya kar raha h re");
        service->sendAlert(push, "kya kar raha h re");
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
