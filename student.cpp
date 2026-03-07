#include "Student.h"
#include "System.h"
#include <iostream>
using namespace std;

Student::Student() : creditAccount(18, 9) {}
Student::Student(string id, string name, int maxCredits, int minCredits)
    : Person(id, name), creditAccount(maxCredits, minCredits) {}

// Enrollment: uses CreditAccount (composition) to enforce credit limits
void Student::enroll(string courseID, int courseCredits) {
    if (courseCredits <= 0) {
        courses.push_back(courseID);
        return;
    }
    if (!creditAccount.canAddCourse(courseCredits)) {
        cout << "Cannot enroll: credit limit would be exceeded (current: "
             << creditAccount.getCurrentCredits() << ", max: " << creditAccount.getMaxCredits() << ").\n";
        return;
    }
    courses.push_back(courseID);
    creditAccount.addCredits(courseCredits);
    cout << "Enrolled in " << courseID << " (" << courseCredits << " credits).\n";
}

void Student::dropCourse(string courseID, int courseCredits) {
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (*it == courseID) {
            if (courseCredits > 0) {
                if (!creditAccount.canDropCourse(courseCredits)) {
                    cout << "Cannot drop: would go below minimum credits.\n";
                    return;
                }
                creditAccount.dropCredits(courseCredits);
            }
            courses.erase(it);
            cout << "Course dropped successfully.\n";
            return;
        }
    }
    cout << "Course not found in your list.\n";
}

// VIEW FUNCTIONS 
void Student::viewGrades(System &sys) {
    cout << "\n--- Your Grades ---\n";
    sys.showGradesForStudent(id);
}

void Student::viewSchedule(System &sys) {
    cout << "\n--- Your Schedule ---\n";
    sys.showScheduleForStudent(id);
}

void Student::viewProgress(System &sys) {
    cout << "\n--- Degree Progress ---\n";
    sys.showProgress(id);
}

void Student::calculateGPA(System &sys) {
    cout << "\n--- GPA ---\n";
    sys.calculateGPA(id);
}

// PROFILE MANAGEMENT

void Student::manageProfile() {
    cout << "\nProfile Info:\n";
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;

    cout << "Update name? (y/n): ";
    char ch;
    cin >> ch;

    if (ch == 'y' || ch == 'Y') {
        cout << "Enter new name: ";
        cin >> name;
        cout << "Profile updated.\n";
    }
}

// VIEW ENROLLED COURSES

void Student::viewEnrolledCourses() {
    cout << "\nEnrolled Courses: ";
    if (courses.empty()) {
        cout << "None";
    } else {
        for (auto &c : courses)
            cout << c << " ";
    }
    cout << endl;
}

// DISPLAY

void Student::display() {
    cout << "Student : " << id << " " << name << endl;

    cout << "Courses: ";
    for (auto &c : courses)
        cout << c << " ";

    cout << endl;
}
string Student::toCSV() const {
    
    return getId() + "," + getName();
}
