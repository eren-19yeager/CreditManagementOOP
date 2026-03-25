#include "faculty.h"
#include "GradeException.h"
#include "system.h"
#include "CourseComponent.h"
#include "TheoryComponent.h"
#include "labComponent.h"
#include "OnlineComponent.h"
#include <bits/stdc++.h>
using namespace std;

Faculty::Faculty() : Person("", "", "") {}
Faculty::Faculty(string id, string name) : Person(id, name, "") {}
Faculty::Faculty(string id, string name, string pass) : Person(id, name, pass) {}

void Faculty::display() {
    cout << "Faculty : " << id << " " << name << "\n";
}

// ---- Simple marks entry — throws GradeException on invalid input ----
void Faculty::enterGrades(System &sys, string studentID, string courseCode, float marks) {
    Course* co = sys.findCourse(courseCode);
    if (!co)
        throw GradeException("Course not found: " + courseCode, studentID, courseCode);

    if (co->getFacultyID() != id)
        throw GradeException("Access denied: " + id + " is not assigned to " + courseCode,
                              studentID, courseCode);

    bool enrolled = false;
    for (const auto &e : sys.enrollments)
        if (e.getStudentID() == studentID && e.getCourseCode() == courseCode
            && e.getStatus() == "Active") { enrolled = true; break; }
    if (!enrolled)
        throw GradeException("Student " + studentID + " is not enrolled in " + courseCode,
                              studentID, courseCode);

    if (marks < 0 || marks > 100)
        throw GradeException("Invalid marks " + to_string((int)marks) +
                              " — must be 0-100", studentID, courseCode);

    sys.assignGrade(studentID, courseCode, marks);
    sys.markCourseCompleted(studentID, courseCode);
    cout << "Grade entered: " << marks << " for student " << studentID
         << " in " << courseCode << ".\n";
}

// ---- Component-based entry ----
void Faculty::enterGradesDetailed(System &sys, string studentID, string courseCode) {
    // Verify course ownership
    Course* co = sys.findCourse(courseCode);
    if (!co) { cout << "Course not found.\n"; return; }
    if (co->getFacultyID() != id) {
        cout << "Access denied: you are not assigned to " << courseCode << ".\n";
        return;
    }
    // Verify student enrollment
    bool enrolled = false;
    for (const auto &e : sys.enrollments)
        if (e.getStudentID() == studentID && e.getCourseCode() == courseCode
            && e.getStatus() == "Active") { enrolled = true; break; }
    if (!enrolled) {
        cout << "Student " << studentID << " is not enrolled in " << courseCode << ".\n";
        return;
    }
    cout << "\n--- Detailed Grade Entry: " << studentID << " / " << courseCode << " ---\n";
    cout << "Select component type:\n";
    cout << "1. Theory  (quizzes + assignment + mid + final)\n";
    cout << "2. Lab     (project + daily eval + written + final lab)\n";
    cout << "3. Online  (Theory + Lab combined)\n";
    cout << "Choice: ";
    int choice;
    if (!(cin >> choice) || choice < 1 || choice > 3) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Invalid choice.\n";
        return;
    }

    CourseComponent* comp = nullptr;
    string compID = studentID + "_" + courseCode;

    if (choice == 1) {
        // Theory
        TheoryComponent* tc = new TheoryComponent(compID);
        float q[4];
        cout << "Enter 4 quiz marks (each out of 25, total contributes 10%):\n";
        for (int i = 0; i < 4; i++) {
            cout << "  Quiz " << i+1 << ": "; cin >> q[i];
        }
        float assign, mid, finalM;
        cout << "Assignment (out of 10): "; cin >> assign;
        cout << "Mid exam   (out of 30): "; cin >> mid;
        cout << "Final exam (out of 50): "; cin >> finalM;
        tc->setTheoryMarks(q, assign, mid, finalM);
        tc->evaluate();
        comp = tc;

    } else if (choice == 2) {
        // Lab
        LabComponent* lc = new LabComponent(compID);
        float p, d, w, f;
        cout << "Project         (out of 30): "; cin >> p;
        cout << "Daily eval      (out of 30): "; cin >> d;
        cout << "Written test    (out of 20): "; cin >> w;
        cout << "Final lab       (out of 20): "; cin >> f;
        lc->setLabMarks(p, d, w, f);
        lc->evaluate();
        comp = lc;

    } else {
        // Online (Theory + Lab)
        OnlineComponent* oc = new OnlineComponent(compID);

        // Theory part
        float q[4];
        cout << "\n-- Theory portion --\n";
        cout << "Enter 4 quiz marks:\n";
        for (int i = 0; i < 4; i++) {
            cout << "  Quiz " << i+1 << ": "; cin >> q[i];
        }
        float assign, mid, finalM;
        cout << "Assignment: "; cin >> assign;
        cout << "Mid exam:   "; cin >> mid;
        cout << "Final exam: "; cin >> finalM;
        oc->setTheoryMarks(q, assign, mid, finalM);

        // Lab part
        float p, d, w, f;
        cout << "\n-- Lab portion --\n";
        cout << "Project:      "; cin >> p;
        cout << "Daily eval:   "; cin >> d;
        cout << "Written test: "; cin >> w;
        cout << "Final lab:    "; cin >> f;
        oc->setLabMarks(p, d, w, f);

        oc->evaluate();
        comp = oc;
    }

    // Store the grade using the component result
    sys.assignGradeFromComponent(studentID, courseCode, comp);
    sys.markCourseCompleted(studentID, courseCode);
    cout << "\nDetailed grade recorded. Final result: " << comp->getResult() << "%\n";
    comp->displayStatus();
}

// ---- Other faculty functions ----

void Faculty::viewTeachingLoad(System &sys) {
    int count = 0;
    cout << "\n--- Teaching load for " << name << " (" << id << ") ---\n";
    for (auto &c : sys.courses) {
        if (c.getFacultyID() == id) {
            count++;
            cout << "   " << c.getCode() << " - " << c.getTitle()
                 << " (" << c.getCredits() << " credits)\n";
        }
    }
    if (count == 0) cout << "  No courses assigned.\n";
    else            cout << "  Total: " << count << " course(s).\n";
}

void Faculty::viewClassList(System &sys, string courseCode) {
    cout << "\n--- Class list for " << courseCode << " ---\n";
    bool any = false;
    for (auto &e : sys.enrollments) {
        if (e.getCourseCode() != courseCode) continue;
        any = true;
        string sname = "(unknown)";
        for (auto &s : sys.students)
            if (s.getId() == e.getStudentID()) { sname = s.getName(); break; }
        cout << "  " << e.getStudentID() << " - " << sname << "\n";
    }
    if (!any) cout << "  No students enrolled.\n";
}

void Faculty::manageCourseMaterials(System &sys, string courseCode) {
    cout << "\n--- Course materials for " << courseCode << " ---\n";
    cout << "  (Upload / add materials feature can be added here.)\n";
}

void Faculty::viewClassSchedule(System &sys, string courseCode) {
    cout << "\n--- Schedule for " << courseCode << " ---\n";
    bool any = false;
    for (auto &s : sys.scheduleEntries) {
        if (s.courseCode == courseCode) {
            any = true;
            cout << "  " << s.dayTime << " (student " << s.studentID << ")\n";
        }
    }
    if (!any) cout << "  No schedule entries for this course.\n";
}
