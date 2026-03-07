#include "System.h"
#include <fstream>
#include <iostream>

using namespace std;

// enroll student
void System::enroll(string studentID, string courseCode) {
    enrollments.push_back({studentID, courseCode});
}

// assign grade
void System::assignGrade(string studentID, string courseCode, float marks) {
    string letter;

    if (marks >= 80) letter = "A";
    else if (marks >= 70) letter = "B";
    else if (marks >= 60) letter = "C";
    else letter = "F";

    grades.push_back({studentID, courseCode, marks, letter});
}

// calculate GPA using Grade entries
void System::calculateGPA(string studentID) {
    float total = 0;
    int count = 0;

    for (auto &g : grades) {
        if (g.studentID == studentID) {
            if (g.letter == "A") total += 4;
            else if (g.letter == "B") total += 3;
            else if (g.letter == "C") total += 2;
            count++;
        }
    }

    if (count > 0)
        cout << "GPA: " << total / count << endl;
    else
        cout << "No grades found.\n";
}

// show all grades for a student
void System::showGradesForStudent(const string &studentID) {
    bool any = false;
    for (auto &g : grades) {
        if (g.studentID == studentID) {
            cout << g.courseCode << " : " << g.marks << " (" << g.letter << ")\n";
            any = true;
        }
    }
    if (!any)
        cout << "No grades recorded.\n";
}

// show schedule for a student
void System::showScheduleForStudent(const string &studentID) {
    bool any = false;
    for (auto &s : schedules) {
        if (s.studentID == studentID) {
            cout << s.courseCode << " - " << s.dayTime << "\n";
            any = true;
        }
    }
    if (!any)
        cout << "No schedule entries.\n";
}

// show degree progress for a student
void System::showProgress(const string &studentID) {
    for (auto &p : progress) {
        if (p.studentID == studentID) {
            cout << "Completed credits: " << p.completedCredits
                 << " / " << p.totalCreditsRequired << "\n";
            return;
        }
    }
    cout << "No progress data.\n";
}

// save courses
void System::saveCourses() {
    ofstream file("data/courses.txt");

    for (auto &c : courses) {
        file << c.getCode() << "," << c.getTitle()
             << "," << c.getCredits() << endl;
    }
}

