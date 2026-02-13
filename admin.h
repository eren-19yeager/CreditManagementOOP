#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
class System;

class Admin : public Person {
private:
    string password;
    System *sys;

public:
    Admin(string id, string name, string pass, System *s);

    bool login(string pass);

    void addStudent(string id, string name);
    void addFaculty(string id, string name);
    void addCourse(string id, string name);
    void assignFacultyToCourse(string facultyID, string courseID);
    void setCreditLimit(int limit);
    void manageCapacity(string courseID, int newCapacity);
    

    void enrollStudent(string studentID, string courseID);
    void viewAll();
};

#endif
