#include "system.h"
#include "admin.h"
#include "student.h"
#include "faculty.h"
#include "person.h"
#include "timeslot.h"
#include "course.h"
#include <bits/stdc++.h>
#include "GradeException.h"
#include "schedule.h"
using namespace std;

static Student* findStudent(System &sys, const string &id) {
    for (auto &s : sys.students) if (s.getId() == id) return &s;
    return nullptr;
}
static Faculty* findFaculty(System &sys, const string &id) {
    for (auto &f : sys.faculties) if (f.getId() == id) return &f;
    return nullptr;
}

// ================================================================
//  ADMIN MENU
// ================================================================
static void adminMenu(System &sys, Admin &admin) {
    int choice = -1, subchoice = -1;
    while (true) {
        cout << "\n---- Admin Menu ----\n";
        cout << "1.  Manage student\n";
        cout << "2.  Add faculty\n";
        cout << "3.  Add course\n";
        cout << "4.  Assign faculty to course\n";
        cout << "5.  View all\n";
        cout << "6.  Set course time slot\n";
        cout << "7.  Delete faculty\n";
        cout << "8.  Mark courses equivalent\n";
        cout << "9.  Set course prerequisite\n";
        cout << "10. View course prerequisites\n";
        cout << "11. Mark course completed for student\n";
        cout << "0.  Logout\n";
        cout << "Choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000,'\n'); continue; }
        if (choice == 0) { cout << "Logging out...\n"; return; }

        string id, name, courseId, facultyId, studentId, dept, sec;
        switch (choice) {

        case 1: {
            while (true) {
                cout << "\n-- Student Management --\n";
                cout << "1. Add student\n2. Delete student\n3. Modify info\n";
                cout << "4. Enroll in course\n5. Update marks\n6. Set progress\n";
                cout << "7. Enable overload for student\n";
                cout << "8. Reset semester credits for student\n";
                cout << "0. Back\n";
                cout << "Choice: ";
                if (!(cin >> subchoice)) { cin.clear(); cin.ignore(1000,'\n'); continue; }
                if (subchoice == 0) break;
                switch (subchoice) {
                case 1: {
                    cout << "Student ID (0=Back): "; cin >> id;
                    if (id=="0") break;
                    if (findStudent(sys,id)) { cout << "ID already exists.\n"; break; }
                    cout << "Name: "; cin >> name;
                    cout << "Section: "; cin >> sec;
                    cout << "Department: "; cin >> dept;
                    admin.addStudent(id, name, sec, dept); sys.saveAll(); break;
                }
                case 2: {
                    cout << "Student ID (0=Back): "; cin >> id;
                    if (id=="0") break;
                    if (!findStudent(sys,id)) { cout << "Not found.\n"; break; }
                    admin.deleteStudent(id); sys.saveAll(); break;
                }
                case 3: {
                    cout << "Student ID (0=Back): "; cin >> id;
                    if (id=="0") break;
                    Student* s = findStudent(sys,id);
                    if (!s) { cout << "Not found.\n"; break; }
                    s->manageProfile(); sys.saveAll(); break;
                }
                case 4: {
                    cout << "Student ID (0=Back): "; cin >> studentId;
                    if (studentId=="0") break;
                    cout << "Course code (0=Back): "; cin >> courseId;
                    if (courseId=="0") break;
                    sys.viewCoursePrerequisites(courseId);
                    admin.enrollStudent(studentId, courseId); sys.saveAll(); break;
                }
                case 5: {
                    cout << "Faculty ID (0=Back): "; cin >> facultyId;
                    if (facultyId=="0") break;
                    Faculty* f = findFaculty(sys, facultyId);
                    if (!f) { cout << "Faculty not found.\n"; break; }
                    cout << "Student ID (0=Back): "; cin >> studentId;
                    if (studentId=="0") break;
                    cout << "Course code (0=Back): "; cin >> courseId;
                    if (courseId=="0" || !sys.findCourse(courseId)) { cout << "Invalid course.\n"; break; }
                    float marks;
                    cout << "Marks (0-100): "; cin >> marks;
                    try {
                        f->enterGrades(sys, studentId, courseId, marks);
                        sys.saveAll();
                    } catch (const GradeException &e) {
                        cout << "Grade error: " << e.what() << "\n";
                    }
                    break;
                }
                case 6: {
                    cout << "Student ID (0=Back): "; cin >> studentId;
                    if (studentId=="0") break;
                    admin.setStudentProgress(studentId); sys.saveAll(); break;
                }
                case 7: {
                    // Admin manually enables overload (bypass GPA check)
                    cout << "Student ID (0=Back): "; cin >> studentId;
                    if (studentId=="0") break;
                    sys.enableOverloadForStudent(studentId); sys.saveAll(); break;
                }
                case 8: {
                    // Reset at start of new semester
                    cout << "Student ID (0=Back): "; cin >> studentId;
                    if (studentId=="0") break;
                    sys.resetSemesterForStudent(studentId); sys.saveAll(); break;
                }
                default: cout << "Invalid.\n";
                }
            }
            break;
        }
        case 2: {
            cout << "Faculty ID (0=Back): "; cin >> id; if (id=="0") break;
            if (findFaculty(sys,id)) { cout << "ID exists.\n"; break; }
            cout << "Name: "; cin >> name; if (name=="0") break;
            admin.addFaculty(id, name); sys.saveAll(); break;
        }
        case 3: {
            cout << "Course code (0=Back): "; cin >> id; if (id=="0") break;
            cout << "Title (no spaces): "; cin >> name; if (name=="0") break;
            admin.addCourse(id, name); sys.saveAll(); break;
        }
        case 4: {
            cout << "Faculty ID (0=Back): "; cin >> facultyId; if (facultyId=="0") break;
            cout << "Course code (0=Back): "; cin >> courseId; if (courseId=="0") break;
            admin.assignFacultyToCourse(facultyId, courseId); sys.saveAll(); break;
        }
        case 5:
            admin.viewAll();
            cout << "\nTotal persons: " << Person::getCount() << "\n";
            break;
        case 6: {
            cout << "Course code (0=Back): "; cin >> courseId; if (courseId=="0") break;
            Course* c = sys.findCourse(courseId);
            if (!c) { cout << "Not found.\n"; break; }
            string day, startTimeStr; int startHr, startMin;
            cout << "Day (e.g. Mon): "; cin >> day; if (day=="0") break;
            cout << "Start time (e.g. 10:30): "; cin >> startTimeStr;
            if (!TimeSlot::parseTimeString(startTimeStr, startHr, startMin))
                { cout << "Invalid time. Using 10:00.\n"; startHr=10; startMin=0; }
            c->setTimeSlot(TimeSlot(day, startHr, startMin, c->getCredits()*30));
            sys.saveAll();
            cout << "Set: " << day << " " << c->getTimeSlot().getStartTimeStr()
                 << "-" << c->getTimeSlot().getEndTimeStr() << "\n";
            break;
        }
        case 7: {
            cout << "Faculty ID (0=Back): "; cin >> facultyId; if (facultyId=="0") break;
            admin.deleteFaculty(facultyId); sys.saveAll(); break;
        }
        case 8: {
            string cA, cB;
            cout << "First course (0=Back): "; cin >> cA; if (cA=="0") break;
            cout << "Second course (0=Back): "; cin >> cB; if (cB=="0") break;
            admin.markCoursesEquivalent(cA, cB); sys.saveAll(); break;
        }
        case 9: {
            cout << "Course to add prereq to (0=Back): "; cin >> courseId; if (courseId=="0") break;
            sys.viewCoursePrerequisites(courseId);
            string prereq;
            cout << "Prerequisite course code (0=Back): "; cin >> prereq; if (prereq=="0") break;
            sys.addPrerequisiteToCourse(courseId, prereq); sys.saveAll(); break;
        }
        case 10: {
            cout << "Course code (0=Back): "; cin >> courseId; if (courseId=="0") break;
            sys.viewCoursePrerequisites(courseId); break;
        }
        case 11: {
            cout << "Student ID (0=Back): "; cin >> studentId; if (studentId=="0") break;
            cout << "Course to mark completed (0=Back): "; cin >> courseId; if (courseId=="0") break;
            sys.markCourseCompleted(studentId, courseId); sys.saveAll(); break;
        }
        default: cout << "Invalid.\n";
        }
    }
}

// ================================================================
//  STUDENT MENU
// ================================================================
static void studentMenu(System &sys, Admin &admin, Student &student) {
    int choice = -1;
    while (true) {
        cout << "\n---- Student Menu (" << student.getId() << ") ----\n";
        cout << "1. Enroll in course\n";
        cout << "2. View enrolled courses\n";
        cout << "3. View grades and GPA\n";
        cout << "4. View weekly schedule\n";
        cout << "5. View degree progress\n";
        cout << "6. Drop course\n";
        cout << "7. View profile\n";
        cout << "8. View credit status\n";
        cout << "9. Check overload eligibility (needs GPA >= 3.75)\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000,'\n'); continue; }
        if (choice == 0) { cout << "Back to main menu.\n"; return; }

        string courseId;
        switch (choice) {
        case 1: {
            // Show credit status first so student knows how many they can still take
            sys.showCreditStatus(student.getId());

            vector<Course*> available = sys.getAvailableCoursesForStudent(student.getId());
            if (available.empty()) {
                cout << "\nNo courses available (all taken, full, conflicting, or credit limit reached).\n";
                break;
            }
            cout << "\n--- Available Courses ---\n";
            for (size_t i = 0; i < available.size(); i++) {
                Course* c = available[i];
                cout << (i+1) << ". " << c->getCode() << " - " << c->getTitle()
                     << " (" << c->getCredits() << " cr, " << c->getCourseTypeString() << ")";
                const TimeSlot& ts = c->getTimeSlot();
                if (!ts.getDay().empty())
                    cout << " | " << ts.getDay() << " "
                         << ts.getStartTimeStr() << "-" << ts.getEndTimeStr();
                cout << "\n";
                const vector<string>& prereqs = c->getPrerequisiteCodes();
                if (!prereqs.empty()) {
                    cout << "   Prereqs: ";
                    for (size_t p = 0; p < prereqs.size(); p++) {
                        cout << prereqs[p];
                        if (p+1 < prereqs.size()) cout << ", ";
                    }
                    cout << "\n";
                }
            }
            cout << "0. Back\nSelect: ";
            int sel;
            if (!(cin >> sel) || sel < 0 || (size_t)sel > available.size()) {
                cin.clear(); cin.ignore(1000,'\n'); cout << "Invalid.\n"; break;
            }
            if (sel == 0) break;
            Course* chosen = available[sel-1];
            sys.displayCourseDetails(*chosen);
            sys.viewCoursePrerequisites(chosen->getCode());
            cout << "1. Confirm  2. Back\nChoice: ";
            int confirm;
            if (!(cin >> confirm) || confirm < 1 || confirm > 2) {
                cin.clear(); cin.ignore(1000,'\n'); break;
            }
            if (confirm == 1) {
                admin.enrollStudent(student.getId(), chosen->getCode());
                sys.saveAll();
            }
            break;
        }
        case 2: student.viewEnrolledCourses(); break;
        case 3:
            student.viewGrades(sys);
            student.calculateGPA(sys);
            break;
        case 4:
            // Full weekly schedule view using Schedule::displayWeeklyView
            student.viewSchedule(sys);
            break;
        case 5: student.viewProgress(sys); break;
        case 6: {
            cout << "Course code to drop (0=Back): "; cin >> courseId;
            if (courseId=="0") break;
            Course* c = sys.findCourse(courseId);
            if (!c) { cout << "Not found.\n"; break; }
            student.dropCourse(courseId, c->getCredits());
            sys.saveAll(); break;
        }
        case 7: student.viewProfile(); break;
        case 8: sys.showCreditStatus(student.getId()); break;
        case 9:
            // Student can check if they qualify for overload (GPA-based)
            sys.checkAndEnableOverload(student.getId());
            sys.saveAll();
            break;
        default: cout << "Invalid.\n";
        }
    }
}

// ================================================================
//  FACULTY MENU
// ================================================================
static void facultyMenu(System &sys, Faculty &faculty) {
    int choice = -1;
    while (true) {
        cout << "\n---- Faculty Menu (" << faculty.getId() << ") ----\n";
        cout << "1. View teaching load\n";
        cout << "2. View class list\n";
        cout << "3. Enter grade (simple marks)\n";
        cout << "4. Enter grade (detailed breakdown)\n";
        cout << "5. View class schedule\n";
        cout << "6. View weekly schedule (all my courses)\n";
        cout << "7. Manage course materials\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000,'\n'); continue; }
        if (choice == 0) { cout << "Back to main menu.\n"; return; }

        string courseId, studentId;
        switch (choice) {
        case 1: faculty.viewTeachingLoad(sys); break;
        case 2: {
            cout << "Course code (0=Back): "; cin >> courseId; if (courseId=="0") break;
            faculty.viewClassList(sys, courseId); break;
        }
        case 3: {
            cout << "Student ID (0=Back): "; cin >> studentId; if (studentId=="0") break;
            cout << "Course code (0=Back): "; cin >> courseId; if (courseId=="0") break;
            float marks; cout << "Marks (0-100): "; cin >> marks;
            try {
                faculty.enterGrades(sys, studentId, courseId, marks);
                sys.saveAll();
            } catch (const GradeException &e) {
                cout << "Grade error: " << e.what() << "\n";
            }
            break;
        }
        case 4: {
            cout << "Student ID (0=Back): "; cin >> studentId; if (studentId=="0") break;
            cout << "Course code (0=Back): "; cin >> courseId; if (courseId=="0") break;
            try {
                faculty.enterGradesDetailed(sys, studentId, courseId);
                sys.saveAll();
            } catch (const GradeException &e) {
                cout << "Grade error: " << e.what() << "\n";
            }
            break;
        }
        case 5: {
            cout << "Course code (0=Back): "; cin >> courseId; if (courseId=="0") break;
            faculty.viewClassSchedule(sys, courseId); break;
        }
        case 6: {
            // Build a Schedule from all courses this faculty teaches
            cout << "\n--- Weekly Schedule for " << faculty.getId() << " ---\n";
            Schedule sched;
            for (auto &c : sys.courses) {
                if (c.getFacultyID() != faculty.getId()) continue;
                const TimeSlot& ts = c.getTimeSlot();
                if (ts.getDay().empty()) continue;
                cout << c.getCode() << " - " << c.getTitle() << ": "
                     << ts.getDay() << " "
                     << ts.getStartTimeStr() << "-" << ts.getEndTimeStr() << "\n";
                sched.addSlot(ts);
            }
            cout << "\n-- Organised view --";
            sched.displayWeeklyView();
            break;
        }
        case 7: {
            cout << "Course code (0=Back): "; cin >> courseId; if (courseId=="0") break;
            faculty.manageCourseMaterials(sys, courseId); break;
        }
        default: cout << "Invalid.\n";
        }
    }
}

// ================================================================
//  MAIN
// ================================================================
int main() {
    System sys;
    Admin admin("100", "Ishtiak Ahmed", "123", &sys);
    cout << "=== University System ===\n";
    sys.loadAll();

    int choice = -1;
    while (true) {
        cout << "\n---- Main Menu ----\n";
        cout << "1. Admin login\n2. Student signup\n3. Student login\n";
        cout << "4. Faculty signup\n5. Faculty login\n0. Exit\n";
        cout << "Choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000,'\n'); continue; }
        if (choice == 0) { cout << "Saving and exiting...\n"; sys.saveAll(); break; }

        string id, pass;
        switch (choice) {
        case 1: {
            string adminId;
            cout << "Admin ID (0=Back): "; cin >> adminId; if (adminId=="0") break;
            cout << "Password (0=Back): "; cin >> pass;    if (pass=="0")    break;
            if (adminId=="100" && admin.login(pass)) {
                cout << "Admin login successful.\n";
                adminMenu(sys, admin);
            } else cout << "Invalid credentials.\n";
            break;
        }
        case 2: {
            cout << "Student ID (0=Back): "; cin >> id; if (id=="0") break;
            Student* s = findStudent(sys, id);
            if (!s) { cout << "ID not found. Contact admin.\n"; break; }
            if (s->getPassword() != "") { cout << "Already signed up. Please login.\n"; break; }
            string dept; cout << "Department: "; cin >> dept;
            s->setDepartment(dept);
            cout << "Set password: "; cin >> pass; if (pass=="0") break;
            s->setPassword(pass); sys.saveAll();
            cout << "Signup successful.\n"; break;
        }
        case 3: {
            cout << "Student ID (0=Back): "; cin >> id; if (id=="0") break;
            cout << "Password (0=Back): ";   cin >> pass; if (pass=="0") break;
            Student* s = findStudent(sys, id);
            if (!s || !s->checkPassword(pass)) { cout << "Invalid credentials.\n"; break; }
            cout << "Login successful.\n";
            studentMenu(sys, admin, *s); break;
        }
        case 4: {
            cout << "Faculty ID (0=Back): "; cin >> id; if (id=="0") break;
            Faculty* f = findFaculty(sys, id);
            if (!f) { cout << "ID not found. Contact admin.\n"; break; }
            if (!f->getPassword().empty()) { cout << "Already signed up. Please login.\n"; break; }
            cout << "Set password: "; cin >> pass; if (pass=="0") break;
            f->setPassword(pass); sys.saveAll();
            cout << "Signup successful.\n"; break;
        }
        case 5: {
            cout << "Faculty ID (0=Back): "; cin >> id; if (id=="0") break;
            cout << "Password (0=Back): ";   cin >> pass; if (pass=="0") break;
            Faculty* f = findFaculty(sys, id);
            if (!f || !f->checkPassword(pass)) { cout << "Invalid credentials.\n"; break; }
            cout << "Login successful.\n";
            facultyMenu(sys, *f); break;
        }
        default: cout << "Invalid.\n";
        }
    }
    return 0;
}
