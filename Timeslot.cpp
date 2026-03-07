#include "TimeSlot.h"

TimeSlot::TimeSlot(string d, int s, int e) {
    day = d;
    startTime = s;
    endTime = e;
}

string TimeSlot::getDay() const { return day; }
int TimeSlot::getStartTime() const { return startTime; }
int TimeSlot::getEndTime() const { return endTime; }

bool TimeSlot::conflictsWith(const TimeSlot& other) const {
    if (day != other.day)
        return false;

    return !(endTime <= other.startTime || startTime >= other.endTime);
}
