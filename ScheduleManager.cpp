#include "ScheduleManager.h"
#include <iostream>

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
                     << course->getCourseTitle() << endl;
            }
        }
    }

    return schedule;
}
