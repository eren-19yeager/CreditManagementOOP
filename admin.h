#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"
class System;

class Admin : public Person {
private:
    string password;
    System *sys;

public:
    Admin(string id, string name, string pass, System *s);
    void display() override;

    bool login(string pass);

    void addStudent(string id, string name,string sec, string dept);
    void addFaculty(string id, string name);
    void addCourse(string id, string name);
    void assignFacultyToCourse(string facultyID, string courseID);
    void setCreditLimit(int limit);
    void manageCapacity(string courseID, int newCapacity);
    void deleteStudent(string id);
    void modifyStudentInfo(string id);
    void modifyCourseInfo(string courseID);
    void deleteFaculty(string id);
    void enrollStudent(string studentID, string courseID);
    void markCoursesEquivalent(string courseA, string courseB);
    void setStudentProgress(string studentID);
    void viewAll();
};

#endif
