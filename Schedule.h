#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "TimeSlot.h"

class Schedule {
private:
    vector<TimeSlot> slots;

public:
    void addSlot(const TimeSlot& slot);
    bool checkConflict(const TimeSlot& slot) const;
    void displayWeeklyView() const;
    const vector<TimeSlot>& getSlots() const;
};

#endif
