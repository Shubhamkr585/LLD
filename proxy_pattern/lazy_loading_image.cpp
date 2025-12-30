#include <iostream>
#include <string>
using namespace std;

// ==========================================
// 1. The Interface
// ==========================================
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() {}
};

// ==========================================
// 2. The Real Subject (Heavy Resource)
// ==========================================
class RealImage : public Image {
private:
    string filename;

    // A helper method to simulate expensive work
    void loadFromDisk(string filename) {
        cout << "   [HDD] Loading " << filename << " (Heavy Operation...)" << endl;
    }

public:
    // Constructor: This is EXPENSIVE. 
    // In the naive approach, this runs immediately for every image.
    RealImage(string filename) : filename(filename) {
        loadFromDisk(filename);
    }

    void display() override {
        cout << "   [GPU] Displaying " << filename << endl;
    }
};

// ==========================================
// 3. The Proxy (Lazy Loader)
// ==========================================
class ProxyImage : public Image {
private:
    RealImage* realImage; // Pointer to the heavy object
    string filename;      // We only store the name first (Lightweight)

public:
    ProxyImage(string filename) : filename(filename), realImage(nullptr) {}

    ~ProxyImage() {
        // If the real image was created, we must delete it
        if (realImage) {
            delete realImage;
        }
    }

    // The Magic Happens Here
    void display() override {
        // 1. Check if the object is created
        if (realImage == nullptr) {
            cout << "--- First time access: creating RealImage ---" << endl;
            realImage = new RealImage(filename); // Expensive call happens NOW
        }
        
        // 2. Delegate the display call
        realImage->display();
    }
};

// ==========================================
// 4. The Client
// ==========================================
int main() {
    cout << "--- Application Starting ---" << endl;

    // 1. Create the Image (Think: Loading a list of files)
    // Notice: NO "Loading from disk" message appears yet! 
    // It's instant because we are only making Proxies.
    Image* img1 = new ProxyImage("Summer_Vacation_4K.jpg");
    Image* img2 = new ProxyImage("Project_Diagram.png");

    cout << "--- Objects Created (No RAM used yet) ---\n" << endl;

    // 2. User clicks on the first image
    cout << "User clicked on Image 1:" << endl;
    img1->display(); // Triggers loading

    cout << "\nUser clicked on Image 1 AGAIN:" << endl;
    img1->display(); // Does NOT trigger loading (Already in RAM)

    // Notice: img2 is NEVER loaded from disk because the user never viewed it.
    // This saves memory.

    delete img1;
    delete img2;
    return 0;
}