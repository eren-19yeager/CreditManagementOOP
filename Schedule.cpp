#include "Schedule.h"
#include <iostream>

using namespace std;

void Schedule::addSlot(const TimeSlot& slot) {
    slots.push_back(slot);
}

bool Schedule::checkConflict(const TimeSlot& newSlot) const {
    for (const auto& s : slots) {
        if (s.conflictsWith(newSlot))
            return true;
    }
    return false;
}

void Schedule::displayWeeklyView() const {
    cout << "\nWeekly Schedule\n";

    for (const auto& s : slots) {
        cout << s.getDay() << " "
             << s.getStartTime()
             << "-"
             << s.getEndTime()
             << endl;
    }
}
const vector<TimeSlot>& Schedule::getSlots() const
{
    return slots;
}
