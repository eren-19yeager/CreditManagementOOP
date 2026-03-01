#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include "CreditAccount.h"
#include <vector>
class System;

// Composition: Student "has-a" CreditAccount
class Student : public Person {
private:
    vector<string> courses;
    CreditAccount creditAccount;

public:
    Student();
    Student(string id, string name, int maxCredits = 18, int minCredits = 9);

    void enroll(string courseID, int courseCredits);
    void display() override;

    void viewGrades(System &sys);
    void viewSchedule(System &sys);
    void viewProgress(System &sys);
    void manageProfile();
    void viewEnrolledCourses();
    void dropCourse(string courseID, int courseCredits);
    void calculateGPA(System &sys);

    bool operator==(const Student &other) const { return id == other.id; }
};

#endif
