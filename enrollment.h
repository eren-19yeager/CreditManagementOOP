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
    Course*  course;
    string   semester;
    string   status;   // "Pending" / "Active" / "Dropped" / "Completed"

public:
    // Constructor
    Enrollment(string id, Student* s, Course* c, string sem = "");

    // Getters
    string   getEnrollmentID() const;
    Student* getStudent()      const;
    Course*  getCourse()       const;
    string   getStudentID()    const;   // delegates to student->getId()
    string   getCourseCode()   const;   // delegates to course->getCode()
    string   getSemester()     const;
    string   getStatus()       const;

    // Core actions (run full business-logic checks)
    bool enroll();
    bool drop();
    void complete();

    // Restore helpers — used ONLY by loadEnrollments() to skip re-checking
    void restoreActive();
    void restoreDropped();

    // Display
    void displayEnrollmentInfo() const;
};

#endif
