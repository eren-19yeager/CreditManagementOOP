#include "Course.h"
#include <iostream>

using namespace std;
Course::Course(string id, string title, string type, int credit, int cap) {
    courseID = id;
    courseTitle = title;
    courseType = type;
    credits = credit;
    capacity = cap;
    enrolledCount = 0;
}
string Course::getCourseID() const {
    return courseID;
}

string Course::getCourseTitle() const {
    return courseTitle;
}

string Course::getCourseType() const {
    return courseType;
}

int Course::getCredits() const {
    return credits;
}

int Course::getCapacity() const {
    return capacity;
}

int Course::getEnrolledCount() const {
    return enrolledCount;
}

string Course::getInstructorID() const {
    return instructorID;
}

// Set Instructor
void Course::setInstructor(string id) {
    instructorID = id;
}

// Add prerequisite
void Course::addPrerequisite(string prereqID) {
    prerequisites.push_back(prereqID);
}

// Check seat availability
bool Course::isSeatAvailable() const {
    return enrolledCount < capacity;
}

// Enroll student
bool Course::enrollStudent() {
    if (isSeatAvailable()) {
        enrolledCount++;
        return true;
    }
    return false;
}

// Drop student
bool Course::dropStudent() {
    if (enrolledCount > 0) {
        enrolledCount--;
        return true;
    }
    return false;
}

// Check prerequisite completion
bool Course::checkPrerequisite(const vector<string>& completedCourses) const {
    for (int i = 0; i < prerequisites.size(); i++) {
        bool found = false;

        for (int j = 0; j < completedCourses.size(); j++) {
            if (prerequisites[i] == completedCourses[j]) {
                found = true;
                break;
            }
        }

        if (!found)
            return false;
    }

    return true;
}

// Display course info
void Course::displayCourseInfo() const {
    cout << "Course ID: " << courseID << endl;
    cout << "Title: " << courseTitle << endl;
    cout << "Type: " << courseType << endl;
    cout << "Credits: " << credits << endl;
    cout << "Instructor: " << instructorID << endl;
    cout << "Seats: " << enrolledCount << "/" << capacity << endl;
}
