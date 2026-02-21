#ifndef FACULTY_H
#define FACULTY_H

#include "Person.h"

class System;

class Faculty : public Person {
public:
    Faculty();
    Faculty(string id, string name);

    void display() override;

    // All methods below need System to read/write grades, enrollments, courses, schedules.
    void enterGrades(System &sys, string studentID, string courseCode, float marks);
    void viewTeachingLoad(System &sys);
    void viewClassList(System &sys, string courseCode);
    void manageCourseMaterials(System &sys, string courseCode);
    void viewClassSchedule(System &sys, string courseCode);
};

#endif
