#ifndef FACULTY_H
#define FACULTY_H

#include "person.h"
class System;

class Faculty : public Person {
public:
    Faculty();
    Faculty(string id, string name);
    Faculty(string id, string name, string pass);

    void display() override;


    void enterGrades        (System &sys, string studentID, string courseCode, float marks);

    void enterGradesDetailed(System &sys, string studentID, string courseCode);

    void viewTeachingLoad    (System &sys);
    void viewClassList       (System &sys, string courseCode);
    void manageCourseMaterials(System &sys, string courseCode);
    void viewClassSchedule   (System &sys, string courseCode);
};

#endif
