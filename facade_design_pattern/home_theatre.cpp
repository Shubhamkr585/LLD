#include <iostream>
#include <string>
using namespace std;

// ==========================================
// 1. The Subsystem Classes (Complex Components)
// ==========================================
class Amplifier {
public:
    void on() { cout << "Amplifier on." << endl; }
    void setVolume(int level) { cout << "Amplifier setting volume to " << level << endl; }
    void off() { cout << "Amplifier off." << endl; }
};

class DvdPlayer {
public:
    void on() { cout << "DVD Player on." << endl; }
    void play(string movie) { cout << "DVD Player playing \"" << movie << "\"" << endl; }
    void stop() { cout << "DVD Player stopped." << endl; }
    void off() { cout << "DVD Player off." << endl; }
};

class Projector {
public:
    void on() { cout << "Projector on." << endl; }
    void wideScreenMode() { cout << "Projector in Widescreen Mode (16x9)." << endl; }
    void off() { cout << "Projector off." << endl; }
};

class Lights {
public:
    void dim(int level) { cout << "Lights dimming to " << level << "%" << endl; }
    void on() { cout << "Lights on." << endl; }
};

// ==========================================
// 2. The Facade
// Hides the complexity.
// ==========================================
class HomeTheaterFacade {
private:
    Amplifier* amp;
    DvdPlayer* dvd;
    Projector* projector;
    Lights* lights;

public:
    // Constructor Injection: Pass the subsystems in
    HomeTheaterFacade(Amplifier* a, DvdPlayer* d, Projector* p, Lights* l) 
        : amp(a), dvd(d), projector(p), lights(l) {}

    // The Simple Interface
    void watchMovie(string movie) {
        cout << "--- Get ready to watch a movie... ---" << endl;
        lights->dim(10);
        projector->on();
        projector->wideScreenMode();
        amp->on();
        amp->setVolume(5);
        dvd->on();
        dvd->play(movie);
    }

    void endMovie() {
        cout << "\n--- Shutting movie theater down... ---" << endl;
        lights->on();
        projector->off();
        amp->off();
        dvd->stop();
        dvd->off();
    }
};

// ==========================================
// 3. The Client
// ==========================================
int main() {
    // 1. Setup (In a real app, this might be done by a Dependency Injection container)
    Amplifier* amp = new Amplifier();
    DvdPlayer* dvd = new DvdPlayer();
    Projector* projector = new Projector();
    Lights* lights = new Lights();

    // 2. Create the Facade
    HomeTheaterFacade* homeTheater = new HomeTheaterFacade(amp, dvd, projector, lights);

    // 3. User Interaction (Look how simple!)
    homeTheater->watchMovie("Raiders of the Lost Ark");
    homeTheater->endMovie();

    // Cleanup
    delete homeTheater; delete amp; delete dvd; delete projector; delete lights;
    return 0;
}