#include "Enrollment.h"
#include "student.h"
#include "course.h"
#include "CreditAccount.h"
#include <bits/stdc++.h>
using namespace std;

// ---------- Constructor ----------
Enrollment::Enrollment(string id, Student* s, Course* c, string sem)
    : enrollmentID(id), student(s), course(c), semester(sem), status("Pending") {}

// ---------- Getters ----------
string   Enrollment::getEnrollmentID() const { return enrollmentID; }
Student* Enrollment::getStudent()      const { return student; }
Course*  Enrollment::getCourse()       const { return course; }
string   Enrollment::getSemester()     const { return semester; }
string   Enrollment::getStatus()       const { return status; }

string Enrollment::getStudentID() const {
    return student ? student->getId() : "";
}

string Enrollment::getCourseCode() const {
    return course ? course->getCode() : "";
}

// ---------- Enroll ----------
bool Enrollment::enroll() {
    if (!course || !student) return false;

    // Seat availability
    if (!course->isSeatAvailable()) return false;

    // Credit limit
    if (!student->getCreditAccount().canAddCourse(course->getCredits()))
        return false;

    // Prerequisites
    if (!course->checkPrerequisite(student->getCompletedCourses()))
        return false;

    // All checks passed
    course->enrollStudent();
    student->getCreditAccount().addCredits(course->getCredits());
    // Add to student's course list (pass 0 — credits already handled above)
    student->enroll(course->getCode(), 0);

    status = "Active";
    return true;
}

// ---------- Drop ----------
bool Enrollment::drop() {
    if (status != "Active") return false;

    course->dropStudent();
    student->getCreditAccount().dropCredits(course->getCredits());
    // Remove from student's course list (pass 0 — credits already handled)
    student->dropCourse(course->getCode(), 0);

    status = "Dropped";
    return true;
}

// ---------- Complete ----------
void Enrollment::complete() { status = "Completed"; }

// ---------- Restore helpers (CSV load only — no business logic) ----------
void Enrollment::restoreActive()  { status = "Active";  }
void Enrollment::restoreDropped() { status = "Dropped"; }

// ---------- Display ----------
void Enrollment::displayEnrollmentInfo() const {
    cout << "Enrollment ID: " << enrollmentID << "\n";
    cout << "Student ID:    " << (student ? student->getId()   : "N/A") << "\n";
    cout << "Course Code:   " << (course  ? course->getCode()  : "N/A") << "\n";
    cout << "Semester:      " << semester << "\n";
    cout << "Status:        " << status   << "\n";
}
