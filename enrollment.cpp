#include "Enrollment.h"
#include "Student.h"
#include "Course.h"
#include "CreditAccount.h"
#include <bits/stdc++.h>

using namespace std;

// Constructor
Enrollment::Enrollment(string id, Student* s, Course* c, string sem) {
    enrollmentID = id;
    student = s;
    course = c;
    semester = sem;
    status = "Pending";
}

// Getters
string Enrollment::getEnrollmentID() const {
    return enrollmentID;
}

Student* Enrollment::getStudent() const {
    return student;
}

Course* Enrollment::getCourse() const {
    return course;
}

string Enrollment::getSemester() const {
    return semester;
}

string Enrollment::getStatus() const {
    return status;
}

// Enroll logic
bool Enrollment::enroll() {

    if (!course->isSeatAvailable())
        return false;

    if (!student->getCreditAccount().canAddCourse(course->getCredits()))
        return false;

    if (!course->checkPrerequisite(student->getCompletedCourses()))
        return false;

    // All checks passed
    course->enrollStudent();
    student->getCreditAccount().addCredits(course->getCredits());

    status = "Active";
    return true;
}

// Drop logic
bool Enrollment::drop() {

    if (status != "Active")
        return false;

    course->dropStudent();
    student->getCreditAccount().dropCredits(course->getCredits());

    status = "Dropped";
    return true;
}

// Mark as completed
void Enrollment::complete() {
    status = "Completed";
}

// Display info
void Enrollment::displayEnrollmentInfo() const {
    cout << "Enrollment ID: " << enrollmentID << endl;
    cout << "Student ID: " << student->getStudentID() << endl;
    cout << "Course ID: " << course->getCourseID() << endl;
    cout << "Semester: " << semester << endl;
    cout << "Status: " << status << endl;
}