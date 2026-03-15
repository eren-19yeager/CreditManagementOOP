#include "timeslot.h"
#include <sstream>
#include <iomanip>
#include <cstdlib>

bool TimeSlot::parseTimeString(const string& s, int& outHour, int& outMin) {
    outHour = 0;
    outMin = 0;
    if (s.empty()) return false;
    size_t pos = s.find(':');
    if (pos == string::npos) pos = s.find('.');
    if (pos == string::npos) {
        try { outHour = stoi(s); return true; } catch (...) { return false; }
    }
    try {
        outHour = stoi(s.substr(0, pos));
        outMin = stoi(s.substr(pos + 1));
        return outHour >= 0 && outHour <= 23 && outMin >= 0 && outMin <= 59;
    } catch (...) { return false; }
}

TimeSlot::TimeSlot(string d, int s, int e) {
    day = d;
    startMinutes = s;
    endMinutes = e;
}

TimeSlot::TimeSlot(string d, int startHr, int startMin, int durationMins) {
    day = d;
    startMinutes = startHr * 60 + startMin;
    endMinutes = startMinutes + durationMins;
}

string TimeSlot::getDay() const { return day; }
int TimeSlot::getStartMinutes() const { return startMinutes; }
int TimeSlot::getEndMinutes() const { return endMinutes; }

string TimeSlot::getStartTimeStr() const {
    int h = startMinutes / 60;
    int m = startMinutes % 60;
    ostringstream oss;
    oss << h << ":" << (m < 10 ? "0" : "") << m;
    return oss.str();
}

string TimeSlot::getEndTimeStr() const {
    int h = endMinutes / 60;
    int m = endMinutes % 60;
    ostringstream oss;
    oss << h << ":" << (m < 10 ? "0" : "") << m;
    return oss.str();
}

bool TimeSlot::conflictsWith(const TimeSlot& other) const {
    if (day != other.day)
        return false;
    return !(endMinutes <= other.startMinutes || startMinutes >= other.endMinutes);
}