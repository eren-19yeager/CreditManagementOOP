#ifndef STUDENT_H
#define STUDENT_H

#include <fstream>
#include <string>
#include "person.h"
#include "CreditAccount.h"
#include <bits/stdc++.h>
#include "grades.h"


class System;

// Composition: Student "has-a" CreditAccount
class Student : public Person {
private:
    vector<string> courses;
    vector<string> completedCourses;   // for prerequisite checks
    string         department;
    string         section;
    CreditAccount  creditAccount;

public:
    Student();
    Student(string id, string name, string pass, string sec, string dept,
            int maxCredits = 18, int minCredits = 9);
    Student(string id, string name, string pass,
            int maxCredits = 18, int minCredits = 9);

    // Enrollment
    bool enroll(const string &courseID, int courseCredits);
    void dropCourse(const string &courseID, int courseCredits);

    // Display (override)
    void display() override;
    void display() const;

    // Views (need System)
    void viewGrades         (System &sys);
    void viewSchedule       (System &sys);
    void viewProgress       (System &sys);
    void calculateGPA       (System &sys);
    void manageProfile      ();
    void viewProfile        () const;
    void viewEnrolledCourses() const;

    // Getters / Setters
    const vector<string>& getCourses()          const;
    const vector<string>& getCompletedCourses() const;
    void addCompletedCourse(const string &courseCode);

    CreditAccount& getCreditAccount();

    string getDepartment() const;
    string getSection()    const;
    void setDepartment(const string &dept);
    void setSection   (const string &sec);

    bool operator==(const Student &other) const { return id == other.id; }

    //File
    void serialize(ofstream &out) const;
    static Student deserialize(const string &line);
};

#endif
