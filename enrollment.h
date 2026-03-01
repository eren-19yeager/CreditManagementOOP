#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <bits/stdc++.h>

using namespace std;

class Student;
class Course;

class Enrollment {
private:
    string enrollmentID;
    Student* student;
    Course* course;

    string semester;
    string status;   // Active / Dropped / Completed

public:
    // Constructor
    Enrollment(string id, Student* s, Course* c, string sem);

    // Getters
    string getEnrollmentID() const;
    Student* getStudent() const;
    Course* getCourse() const;
    string getSemester() const;
    string getStatus() const;

    // Core actions
    bool enroll();
    bool drop();
    void complete();

    // Utility
    void displayEnrollmentInfo() const;
};

#endif