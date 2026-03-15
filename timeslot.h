#ifndef TIMESLOT_H
#define TIMESLOT_H
#include <bits/stdc++.h>
using namespace std;

// Times stored as minutes since midnight (e.g. 10:30 = 630, 12:00 = 720)
// 1 credit = 30 mins, so 3 credits = 90 mins
class TimeSlot {
private:
    string day;
    int startMinutes;
    int endMinutes;

public:
    TimeSlot(string d = "", int s = 0, int e = 0);
    TimeSlot(string d, int startHr, int startMin, int durationMins);

    string getDay() const;
    int getStartMinutes() const;
    int getEndMinutes() const;
    int getStartTime() const { return startMinutes / 60; }
    int getEndTime() const { return endMinutes / 60; }
    string getStartTimeStr() const;
    string getEndTimeStr() const;

    bool conflictsWith(const TimeSlot& other) const;

    static bool parseTimeString(const string& s, int& outHour, int& outMin);
};

#endif