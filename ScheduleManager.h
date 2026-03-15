#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H
#include <bits/stdc++.h>
#include "schedule.h"
#include "student.h"
#include "system.h"

class ScheduleManager
{
public:
    Schedule generateSchedule(Student& student, System& sys);
    bool detectConflicts(const Schedule& schedule);
};

#endif