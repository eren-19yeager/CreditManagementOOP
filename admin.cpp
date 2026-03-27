#include "admin.h"
#include "system.h"
#include "student.h"
#include "faculty.h"
#include "course.h"
#include "progress.h"
#include "timeslot.h"
#include <bits/stdc++.h>
using namespace std;

Admin::Admin(string id, string name, string pass, System *s)
    : Person(id, name, pass), sys(s) {
    password = pass;
}

void Admin::display() {
    cout << "Admin : " << id << " " << name << "\n";
}

bool Admin::login(string pass) {
    return pass == password;
}

void Admin::addStudent(string id, string name, string sec, string dept) {
    sys->students.push_back(Student(id, name, "", sec, dept, sys->maxCreditsAllowed, 9));
    cout << "Student " << id << " added. Student must sign up with this ID to set password.\n";
}

void Admin::deleteStudent(string id) {
    for (auto it = sys->students.begin(); it != sys->students.end(); ++it) {
        if (it->getId() == id) {
            sys->students.erase(it);
            cout << "Student " << id << " deleted.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void Admin::modifyStudentInfo(string id) {
    for (auto &st : sys->students) {
        if (st.getId() == id) {
            st.manageProfile();
            return;
        }
    }
    cout << "Student not found.\n";
}

void Admin::deleteFaculty(string id) {
    for (auto it = sys->faculties.begin(); it != sys->faculties.end(); ++it) {
        if (it->getId() == id) {
            for (auto &c : sys->courses)
                if (c.getFacultyID() == id) c.assignFaculty("");
            sys->faculties.erase(it);
            cout << "Faculty " << id << " deleted.\n";
            return;
        }
    }
    cout << "Faculty not found.\n";
}

void Admin::addFaculty(string id, string name) {
    sys->faculties.push_back(Faculty(id, name, ""));
    cout << "Faculty " << id << " added. Faculty must sign up with this ID to set password.\n";
}

void Admin::addCourse(string id, string name) {
    int credits;
    cout << "Enter credits for course " << id << " (" << name << "): ";
    cin >> credits;

    int typeChoice;
    cout << "Course type: 1=Theory, 2=Lab, 3=Online: ";
    cin >> typeChoice;
    CourseType ctype = CourseType::Theory;
    if (typeChoice == 2) ctype = CourseType::Lab;
    else if (typeChoice == 3) ctype = CourseType::Online;

    Course c(id, name, credits);
    c.setCourseType(ctype);

    string day, startTimeStr;
    int startHr, startMin;
    cout << "Enter schedule - day (e.g. Mon): ";
    cin >> day;
    cout << "Start time (e.g. 10:30): ";
    cin >> startTimeStr;
    if (!TimeSlot::parseTimeString(startTimeStr, startHr, startMin)) {
        cout << "Invalid time format. Defaulting to 10:00.\n";
        startHr = 10; startMin = 0;
    }
    int durationMins = credits * 30;
    c.setTimeSlot(TimeSlot(day, startHr, startMin, durationMins));

    sys->courses.push_back(c);
    cout << "Course added: " << id << " - " << name
         << " (" << credits << " credits, " << c.getCourseTypeString()
         << ", " << day << " "
         << c.getTimeSlot().getStartTimeStr() << "-"
         << c.getTimeSlot().getEndTimeStr() << ")\n";
}

void Admin::enrollStudent(string studentID, string courseID) {
    Course* course = sys->findCourse(courseID);
    if (!course) { cout << "Course not found.\n"; return; }

    Student* student = sys->findStudent(studentID);
    if (!student) { cout << "Student not found.\n"; return; }

    // Duplicate / equivalent check
    const vector<string>& enrolled = student->getCourses();
    vector<string> similarCodes = course->getSimilarCourseCodes();
    for (const auto& ec : enrolled) {
        for (const auto& sc : similarCodes) {
            if (ec == sc) {
                cout << "Cannot enroll: student is already taking " << ec
                     << ", which is similar/equivalent to " << courseID << ".\n";
                return;
            }
        }
    }

    // Check prerequisites before enrolling
    if (!sys->checkStudentPrerequisites(studentID, courseID)) {
        cout << "Enrollment blocked: prerequisites not met.\n";
        return;
    }
    // Delegate to System::enroll which creates the Enrollment object
    sys->enroll(studentID, courseID);
}

void Admin::setStudentProgress(string studentID) {
    Student* s = sys->findStudent(studentID);
    if (!s) { cout << "Student not found.\n"; return; }

    DegreeProgress* p = nullptr;
    for (auto &pr : sys->progress)
        if (pr.studentID == studentID) { p = &pr; break; }

    if (!p) {
        DegreeProgress newP;
        newP.studentID = studentID;
        newP.semester = 1;
        newP.semesterFinalsAttempted = 0;
        newP.semesterFinalsPassed = 0;
        sys->progress.push_back(newP);
        p = &sys->progress.back();
    }

    cout << "Set semester: ";
    cin >> p->semester;
    cout << "Set academic year: ";
    cin >> p->academicYear;
    cout << "Semester finals attempted: ";
    cin >> p->semesterFinalsAttempted;
    cout << "Semester finals passed: ";
    cin >> p->semesterFinalsPassed;
    cout << "Progress updated for " << studentID << ".\n";
}

void Admin::markCoursesEquivalent(string courseA, string courseB) {
    Course* cA = sys->findCourse(courseA);
    Course* cB = sys->findCourse(courseB);
    if (!cA) { cout << "Course " << courseA << " not found.\n"; return; }
    if (!cB) { cout << "Course " << courseB << " not found.\n"; return; }
    cA->addEquivalentCourse(courseB);
    cB->addEquivalentCourse(courseA);
    cout << "Courses " << courseA << " and " << courseB << " marked as equivalent.\n";
}

void Admin::assignFacultyToCourse(string facultyID, string courseID) {
    for (auto &c : sys->courses) {
        if (c.getCode() == courseID) {
            c.assignFaculty(facultyID);
            cout << "Faculty " << facultyID << " assigned to " << courseID << ".\n";
            return;
        }
    }
    cout << "Course not found.\n";
}

void Admin::setCreditLimit(int limit) {
    sys->maxCreditsAllowed = limit;
    cout << "Credit limit set to " << limit << " (for new students).\n";
}

void Admin::manageCapacity(string courseID, int newCapacity) {
    for (auto &c : sys->courses) {
        if (c.getCode() == courseID) {
            c.setCapacity(newCapacity);
            cout << "Capacity for " << courseID << " set to " << newCapacity << ".\n";
            return;
        }
    }
    cout << "Course not found.\n";
}

static void displayPerson(Person &p) { p.display(); }

void Admin::viewAll() {
    cout << "\nStudents:\n";
    for (auto &s : sys->students)
        cout << "  " << s << "\n";  // uses Student::operator<<

    cout << "\nFaculty:\n";
    for (auto &f : sys->faculties) displayPerson(f);

    cout << "\nCourses:\n";
    // operator<< prints: code - title (credits) | Faculty: X | enrolled/capacity seats
    for (auto &c : sys->courses) {
        cout << "  " << c;   // uses Course::operator<<
        const TimeSlot& ts = c.getTimeSlot();
        if (!ts.getDay().empty() && ts.getEndMinutes() > ts.getStartMinutes())
            cout << " | " << ts.getDay() << " "
                 << ts.getStartTimeStr() << "-" << ts.getEndTimeStr();
        else
            cout << " | Schedule: Not set";
        cout << "\n";
    }
}
