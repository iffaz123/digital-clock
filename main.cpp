#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <ctime>
#include <map>

using namespace std;

void displayLocalTime() {
    while (true) {
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);

        cout << "\033[2J\033[1;1H";

        string ampm;
        int hour = localTime->tm_hour % 12;
        if (hour == 0) hour = 12;

        ampm = (localTime->tm_hour < 12) ? "AM" : "PM";

        cout << "+--------------------------+" << endl;
        cout << "|       Digital Clock      |" << endl;
        cout << "+--------------------------+" << endl;
        cout << "|       Current Time       |" << endl;
        cout << "+--------------------------+" << endl;
        cout << "| " << setw(2) << setfill('0') << hour << " | "
             << setw(2) << setfill('0') << localTime->tm_min << " | "
             << setw(2) << setfill('0') << localTime->tm_sec << " | " << ampm << endl;
        cout << "+--------------------------+" << endl;

        this_thread::sleep_for(chrono::seconds(1));
    }
}

void displayWorldTime(int offset, const string& timezone) {
    while (true) {
        time_t currentTime = time(nullptr);
        time_t worldTime = currentTime + offset * 3600;
        tm* worldLocalTime = localtime(&worldTime);

        string ampmWorld;
        int hourWorld = worldLocalTime->tm_hour % 12;
        if (hourWorld == 0) hourWorld = 12;

        ampmWorld = (worldLocalTime->tm_hour < 12) ? "AM" : "PM";

        cout << "+--------------------------+" << endl;
        cout << "| " << timezone << " Time (GMT " << (offset >= 0 ? "+" : "") << offset << ")     |" << endl;
        cout << "+--------------------------+" << endl;
        cout << "| " << setw(2) << setfill('0') << hourWorld << " | "
             << setw(2) << setfill('0') << worldLocalTime->tm_min << " | "
             << setw(2) << setfill('0') << worldLocalTime->tm_sec << " | " << ampmWorld << endl;
        cout << "+--------------------------+" << endl;

        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    map<string, int> timeZones;
    timeZones["New York"] = -11;
    timeZones["London"] = -6;
    timeZones["Tokyo"] = +3;
    timeZones["Sydney"] = +5;
    timeZones["Dubai"] = -2;

    thread localThread(displayLocalTime);
    localThread.detach();

    string country;
    while (true) {
        cout << "Enter country name: ";
        cin >> country;

        if (timeZones.find(country) != timeZones.end()) {
            thread worldThread(displayWorldTime, timeZones[country], country);
            worldThread.detach();
        } else {
            cout << "Time zone for " << country << " not found." << endl;
        }
    }

    return 0;
}

