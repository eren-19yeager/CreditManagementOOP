#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <string>
using namespace std;

class TimeSlot {
private:
    string day;
    int startTime;
    int endTime;

public:
    TimeSlot(string d = "", int s = 0, int e = 0);

    string getDay() const;
    int getStartTime() const;
    int getEndTime() const;

    bool conflictsWith(const TimeSlot& other) const;
};

#endif
