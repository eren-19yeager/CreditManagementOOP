#include "ScheduleManager.h"
#include <bits/stdc++.h>
using namespace std;

Schedule ScheduleManager::generateSchedule(Student& student, System& sys)
{
    Schedule schedule;

    vector<string> courseIDs = student.getCourses();

    for (auto &id : courseIDs)
    {
        Course* course = sys.findCourse(id);

        if(course != nullptr)
        {
            TimeSlot slot = course->getTimeSlot();

            if(!schedule.checkConflict(slot))
            {
                schedule.addSlot(slot);
            }
            else
            {
                cout << "Conflict detected for course "
                     << course->getTitle() << endl;
            }
        }
    }

    return schedule;
}

bool ScheduleManager::detectConflicts(const Schedule& schedule) {
    const vector<TimeSlot>& slots = schedule.getSlots();
    for (size_t i = 0; i < slots.size(); ++i) {
        for (size_t j = i + 1; j < slots.size(); ++j) {
            if (slots[i].conflictsWith(slots[j]))
                return true;
        }
    }
    return false;
}