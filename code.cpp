#include <iostream>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <string>

using namespace std;

class TrafficSignal {
private:
    int greenTime;
    int redTime;
    int pedestrianTime;
    int trafficDensity;
    unordered_map<string, int> finesDatabase;

public:
    TrafficSignal(int green, int red, int pedestrian)
        : greenTime(green), redTime(red), pedestrianTime(pedestrian), trafficDensity(0) {}

    void adjustSignal(int density) {
        trafficDensity = density;
        if (trafficDensity > 50) {
            greenTime += 10;
            redTime -= 10;
        } else {
            greenTime = 30;
            redTime = 30;
        }
    }

    void runSignal() {
        while (true) {
            cout << "Green Light - Vehicles Go! (Duration: " << greenTime << " seconds)\n";
            this_thread::sleep_for(chrono::seconds(greenTime));

            cout << "Yellow Light - Prepare to Stop! (Duration: 5 seconds)\n";
            this_thread::sleep_for(chrono::seconds(5));

            cout << "Red Light - Vehicles Stop! Pedestrians Crossing (Duration: " << pedestrianTime << " seconds)\n";
            this_thread::sleep_for(chrono::seconds(pedestrianTime));

            simulateViolation();
        }
    }

    void simulateViolation() {
        string vehiclePlate = "ABC123";
        bool isViolation = true;

        if (isViolation) {
            cout << "Violation Detected! Vehicle " << vehiclePlate << " did not stop for pedestrians.\n";
            issueFine(vehiclePlate);
        }
    }

    void issueFine(const string& vehiclePlate) {
        int fineAmount = 500;
        finesDatabase[vehiclePlate] += fineAmount;
        cout << "Fine of " << fineAmount << " issued to vehicle " << vehiclePlate << ".\n";
        cout << "Total fines for " << vehiclePlate << ": " << finesDatabase[vehiclePlate] << "\n";
    }

    void displayFines() const {
        cout << "\nFines Database:\n";
        for (const auto& entry : finesDatabase) {
            cout << "Vehicle: " << entry.first << ", Total Fines: " << entry.second << "\n";
        }
    }
};

int main() {
    TrafficSignal signal(30, 30, 20);

    int trafficDensity;
    cout << "Enter traffic density (0-100): ";
    cin >> trafficDensity;

    signal.adjustSignal(trafficDensity);

    thread signalThread(&TrafficSignal::runSignal, &signal);

    this_thread::sleep_for(chrono::seconds(120));

    signal.displayFines();

    signalThread.join();

    return 0;
}
