#include "Faculty.h"
#include "System.h"
#include <iostream>

using namespace std;

Faculty::Faculty() {}
Faculty::Faculty(string id, string name) : Person(id, name) {}

void Faculty::display() {
    cout << "Faculty : " << id << " " << name << endl;
}

void Faculty::enterGrades(System &sys, string studentID, string courseCode, float marks) {
    if (marks < 0 || marks > 100) {
        cout << "Invalid marks. Use 0-100.\n";
        return;
    }
    sys.assignGrade(studentID, courseCode, marks);
    cout << "Grade entered: " << marks << " for student " << studentID
         << " in " << courseCode << ".\n";
}

void Faculty::viewTeachingLoad(System &sys) {
    int count = 0;
    cout << "\n--- Teaching load for " << name << " (" << id << ") ---\n";
    for (auto &c : sys.courses) {
        if (c.getFacultyID() == id) {
            count++;
            cout << "  " << c.getCode() << " - " << c.getTitle()
                 << " (" << c.getCredits() << " credits)\n";
        }
    }
    if (count == 0)
        cout << "  No courses assigned.\n";
    else
        cout << "Total: " << count << " course(s).\n";
}

// Show all students enrolled in a given course.
// Uses System's enrollments list: print each studentID (and name if found) for that courseCode.
void Faculty::viewClassList(System &sys, string courseCode) {
    cout << "\n--- Class list for " << courseCode << " ---\n";
    bool any = false;
    for (auto &e : sys.enrollments) {
        if (e.courseCode != courseCode) continue;
        any = true;
        string name = "(unknown)";
        for (auto &s : sys.students) {
            if (s.getId() == e.studentID) {
                name = s.getName();
                break;
            }
        }
        cout << "  " << e.studentID << " - " << name << "\n";
    }
    if (!any)
        cout << "  No students enrolled.\n";
}

void Faculty::manageCourseMaterials(System &sys, string courseCode) {
    cout << "\n--- Course materials for " << courseCode << " ---\n";
    cout << "  (Upload / add materials feature can be added here.)\n";
}

void Faculty::viewClassSchedule(System &sys, string courseCode) {
    cout << "\n--- Schedule for " << courseCode << " ---\n";
    bool any = false;
    for (auto &s : sys.schedules) {
        if (s.courseCode == courseCode) {
            any = true;
            cout << "  " << s.dayTime << " (student " << s.studentID << ")\n";
        }
    }
    if (!any)
        cout << "  No schedule entries for this course.\n";
}

