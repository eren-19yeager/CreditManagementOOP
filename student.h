#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include "CreditAccount.h"
#include <bits/stdc++.h>
#include <iostream>
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
    //File
    void serialize(ofstream &out) const;
    static Student deserialize(const string &line);

    bool operator==(const Student &other) const { return id == other.id; }

    // Stream output: prints student summary
    friend ostream& operator<<(ostream &os, const Student &s) {
        os << "ID: " << s.id << " | Name: " << s.name
           << " | Dept: " << (s.department.empty() ? "Not set" : s.department)
           << " | Credits: " << s.creditAccount.getCurrentCredits();
        return os;
    }
};

#endif
