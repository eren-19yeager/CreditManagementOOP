#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include "Schedule.h"
#include "Student.h"
#include "System.h"

class ScheduleManager
{
public:
    Schedule generateSchedule(Student& student, System& sys);
    bool detectConflicts(const Schedule& schedule);
};

#endif
