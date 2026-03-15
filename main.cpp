#include "system.h"
#include "admin.h"
#include "student.h"
#include "faculty.h"
#include "person.h"
#include "timeslot.h"
#include "course.h"
#include <bits/stdc++.h>
using namespace std;

static Student* findStudent(System &sys, const string &id) {
    for (auto &s : sys.students)
        if (s.getId() == id) return &s;
    return nullptr;
}

static Faculty* findFaculty(System &sys, const string &id) {
    for (auto &f : sys.faculties)
        if (f.getId() == id) return &f;
    return nullptr;
}

static void adminMenu(System &sys, Admin &admin) {
    int choice = -1;
    int subchoice = -1;
    while (true) {
        cout << "\n---- Admin Menu ----\n";
        cout << "1.  Manage student\n";
        cout << "2.  Add faculty\n";
        cout << "3.  Add course\n";
        cout << "4.  Assign faculty to course\n";
        cout << "5.  View all (admin overview)\n";
        cout << "6.  Set course time slot\n";
        cout << "7.  Delete faculty\n";
        cout << "8.  Mark courses equivalent\n";
        cout << "9.  Set course prerequisite\n";
        cout << "10. View course prerequisites\n";
        cout << "11. Mark course completed for student\n";
        cout << "0.  Back / Logout\n";
        cout << "Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            cout << "Logging out of admin account...\n";
            return;
        }

        string id, name, courseId, facultyId, studentId, dept, sec;
        switch (choice) {

        // ---- Manage student ----
        case 1: {
            while (true) {
                cout << "\n-- Student Management --\n";
                cout << "1. Add student\n";
                cout << "2. Delete student\n";
                cout << "3. Modify student info\n";
                cout << "4. Enroll student in course\n";
                cout << "5. Update marks\n";
                cout << "6. Set student progress\n";
                cout << "0. Back\n";
                cout << "Choice: ";
                if (!(cin >> subchoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (subchoice == 0) break;

                switch (subchoice) {
                case 1: {
                    cout << "Enter student ID (0 = Back): ";
                    cin >> id;
                    if (id == "0") { cout << "Cancelled.\n"; break; }
                    if (findStudent(sys, id)) {
                        cout << "Student ID already exists.\n"; break;
                    }
                    cout << "Enter student name (0 = Back): ";
                    cin >> name;
                    if (name == "0") { cout << "Cancelled.\n"; break; }
                    cout << "Assign section (0 = Back): ";
                    cin >> sec;
                    if (sec == "0") { cout << "Cancelled.\n"; break; }
                    cout << "Enter department (0 = Back): ";
                    cin >> dept;
                    if (dept == "0") { cout << "Cancelled.\n"; break; }
                    admin.addStudent(id, name, sec, dept);
                    sys.saveAll();
                    break;
                }
                case 2: {
                    cout << "Enter student ID to delete (0 = Back): ";
                    cin >> id;
                    if (id == "0") { cout << "Cancelled.\n"; break; }
                    if (!findStudent(sys, id)) { cout << "Student not found.\n"; break; }
                    admin.deleteStudent(id);
                    sys.saveAll();
                    break;
                }
                case 3: {
                    cout << "Enter student ID to modify (0 = Back): ";
                    cin >> id;
                    if (id == "0") { cout << "Cancelled.\n"; break; }
                    Student* s = findStudent(sys, id);
                    if (!s) { cout << "Student not found.\n"; break; }
                    s->manageProfile();
                    sys.saveAll();
                    break;
                }
                case 4: {
                    cout << "Enter student ID (0 = Back): ";
                    cin >> studentId;
                    if (studentId == "0") { cout << "Cancelled.\n"; break; }
                    cout << "Enter course code (0 = Back): ";
                    cin >> courseId;
                    if (courseId == "0") { cout << "Cancelled.\n"; break; }
                    // Show prerequisites before enrolling
                    sys.viewCoursePrerequisites(courseId);
                    admin.enrollStudent(studentId, courseId);
                    sys.saveAll();
                    break;
                }
                case 5: {
                    cout << "Enter faculty ID (0 = Back): ";
                    cin >> facultyId;
                    if (facultyId == "0") { cout << "Cancelled.\n"; break; }
                    Faculty* f = findFaculty(sys, facultyId);
                    if (!f) { cout << "Faculty not found.\n"; break; }
                    cout << "Enter student ID (0 = Back): ";
                    cin >> studentId;
                    if (studentId == "0") { cout << "Cancelled.\n"; break; }
                    cout << "Enter course code (0 = Back): ";
                    cin >> courseId;
                    if (courseId == "0" || !sys.findCourse(courseId)) {
                        cout << "Invalid course ID.\n"; break;
                    }
                    float marks;
                    cout << "Enter marks (0-100): ";
                    cin >> marks;
                    f->enterGrades(sys, studentId, courseId, marks);
                    sys.saveAll();
                    break;
                }
                case 6: {
                    cout << "Enter student ID (0 = Back): ";
                    cin >> studentId;
                    if (studentId == "0") { cout << "Cancelled.\n"; break; }
                    admin.setStudentProgress(studentId);
                    sys.saveAll();
                    break;
                }
                default:
                    cout << "Invalid choice.\n";
                    break;
                }
            }
            break;
        }

        // ---- Add faculty ----
        case 2: {
            cout << "Enter faculty ID (0 = Back): ";
            cin >> id;
            if (id == "0") { cout << "Cancelled.\n"; break; }
            if (findFaculty(sys, id)) {
                cout << "Faculty ID already exists.\n"; break;
            }
            cout << "Enter faculty name (0 = Back): ";
            cin >> name;
            if (name == "0") { cout << "Cancelled.\n"; break; }
            admin.addFaculty(id, name);
            sys.saveAll();
            break;
        }

        // ---- Add course ----
        case 3: {
            cout << "Enter course code (0 = Back): ";
            cin >> id;
            if (id == "0") { cout << "Cancelled.\n"; break; }
            cout << "Enter course title (no spaces, 0 = Back): ";
            cin >> name;
            if (name == "0") { cout << "Cancelled.\n"; break; }
            admin.addCourse(id, name);
            sys.saveAll();
            break;
        }

        // ---- Assign faculty to course ----
        case 4: {
            cout << "Enter faculty ID (0 = Back): ";
            cin >> facultyId;
            if (facultyId == "0") { cout << "Cancelled.\n"; break; }
            cout << "Enter course code (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            admin.assignFacultyToCourse(facultyId, courseId);
            sys.saveAll();
            break;
        }

        // ---- View all ----
        case 5:
            admin.viewAll();
            cout << "\nTotal persons in system: " << Person::getCount() << "\n";
            break;

        // ---- Set course time slot ----
        case 6: {
            cout << "Enter course code (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            Course* c = sys.findCourse(courseId);
            if (!c) { cout << "Course not found.\n"; break; }
            string day, startTimeStr;
            int startHr, startMin;
            cout << "Enter day (e.g. Mon, 0 = Back): ";
            cin >> day;
            if (day == "0") { cout << "Cancelled.\n"; break; }
            cout << "Start time (e.g. 10:30): ";
            cin >> startTimeStr;
            if (!TimeSlot::parseTimeString(startTimeStr, startHr, startMin)) {
                cout << "Invalid time format. Defaulting to 10:00.\n";
                startHr = 10; startMin = 0;
            }
            int durationMins = c->getCredits() * 30;
            c->setTimeSlot(TimeSlot(day, startHr, startMin, durationMins));
            sys.saveAll();
            cout << "Time slot set: " << day << " "
                 << c->getTimeSlot().getStartTimeStr() << "-"
                 << c->getTimeSlot().getEndTimeStr() << "\n";
            break;
        }

        // ---- Delete faculty ----
        case 7: {
            cout << "Enter faculty ID to delete (0 = Back): ";
            cin >> facultyId;
            if (facultyId == "0") { cout << "Cancelled.\n"; break; }
            admin.deleteFaculty(facultyId);
            sys.saveAll();
            break;
        }

        // ---- Mark courses equivalent ----
        case 8: {
            string courseA, courseB;
            cout << "Enter first course code (0 = Back): ";
            cin >> courseA;
            if (courseA == "0") { cout << "Cancelled.\n"; break; }
            cout << "Enter second course code (0 = Back): ";
            cin >> courseB;
            if (courseB == "0") { cout << "Cancelled.\n"; break; }
            admin.markCoursesEquivalent(courseA, courseB);
            sys.saveAll();
            break;
        }

        // ---- Set course prerequisite ----
        case 9: {
            cout << "Enter course code to add prerequisite to (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            // Show existing prerequisites first
            sys.viewCoursePrerequisites(courseId);
            string prereqCode;
            cout << "Enter prerequisite course code (0 = Back): ";
            cin >> prereqCode;
            if (prereqCode == "0") { cout << "Cancelled.\n"; break; }
            sys.addPrerequisiteToCourse(courseId, prereqCode);
            sys.saveAll();
            break;
        }

        // ---- View course prerequisites ----
        case 10: {
            cout << "Enter course code (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            sys.viewCoursePrerequisites(courseId);
            break;
        }

        // ---- Mark course completed for student ----
        case 11: {
            cout << "Enter student ID (0 = Back): ";
            cin >> studentId;
            if (studentId == "0") { cout << "Cancelled.\n"; break; }
            cout << "Enter course code to mark as completed (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            sys.markCourseCompleted(studentId, courseId);
            sys.saveAll();
            break;
        }

        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

static void studentMenu(System &sys, Admin &admin, Student &student) {
    int choice = -1;
    while (true) {
        cout << "\n---- Student Menu (" << student.getId() << ") ----\n";
        cout << "1. Enroll in course\n";
        cout << "2. View enrolled courses\n";
        cout << "3. View grades and GPA\n";
        cout << "4. View schedule\n";
        cout << "5. View progress\n";
        cout << "6. Drop course\n";
        cout << "7. View profile\n";
        cout << "0. Back / Logout\n";
        cout << "Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice == 0) { cout << "Back to main menu.\n"; return; }

        string courseId;
        switch (choice) {
        case 1: {
            vector<Course*> available = sys.getAvailableCoursesForStudent(student.getId());
            if (available.empty()) {
                cout << "\nNo courses available to enroll.\n";
                break;
            }
            cout << "\n--- Available Courses ---\n";
            for (size_t i = 0; i < available.size(); i++) {
                Course* c = available[i];
                cout << (i + 1) << ". " << c->getCode() << " - " << c->getTitle()
                     << " (" << c->getCredits() << " cr, " << c->getCourseTypeString() << ")\n";
                // Show prerequisites inline
                const vector<string>& prereqs = c->getPrerequisiteCodes();
                if (!prereqs.empty()) {
                    cout << "   Prerequisites: ";
                    for (size_t p = 0; p < prereqs.size(); p++) {
                        cout << prereqs[p];
                        if (p + 1 < prereqs.size()) cout << ", ";
                    }
                    cout << "\n";
                }
            }
            cout << "0. Back\n";
            cout << "Select course number: ";
            int sel;
            if (!(cin >> sel) || sel < 0 || (size_t)sel > available.size()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice.\n";
                break;
            }
            if (sel == 0) break;

            Course* chosen = available[sel - 1];
            sys.displayCourseDetails(*chosen);
            sys.viewCoursePrerequisites(chosen->getCode());

            cout << "1. Confirm enrollment\n";
            cout << "2. Back\n";
            cout << "Choice: ";
            int confirm;
            if (!(cin >> confirm) || confirm < 1 || confirm > 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice.\n";
                break;
            }
            if (confirm == 1) {
                admin.enrollStudent(student.getId(), chosen->getCode());
                sys.saveAll();
            }
            break;
        }
        case 2:
            student.viewEnrolledCourses();
            break;
        case 3:
            student.viewGrades(sys);
            student.calculateGPA(sys);
            break;
        case 4:
            student.viewSchedule(sys);
            break;
        case 5:
            student.viewProgress(sys);
            break;
        case 6: {
            cout << "Enter course code to drop (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            Course* c = sys.findCourse(courseId);
            if (!c) { cout << "Course not found.\n"; break; }
            student.dropCourse(courseId, c->getCredits());
            sys.saveAll();
            break;
        }
        case 7:
            student.viewProfile();
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

static void facultyMenu(System &sys, Faculty &faculty) {
    int choice = -1;
    while (true) {
        cout << "\n---- Faculty Menu (" << faculty.getId() << ") ----\n";
        cout << "1. View teaching load\n";
        cout << "2. View class list\n";
        cout << "3. Enter grade (simple marks)\n";
        cout << "4. View class schedule\n";
        cout << "5. Manage course materials\n";
        cout << "6. Enter grade (detailed - Theory/Lab/Online breakdown)\n";
        cout << "0. Back / Logout\n";
        cout << "Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice == 0) { cout << "Back to main menu.\n"; return; }

        string courseId, studentId;
        switch (choice) {
        case 1:
            faculty.viewTeachingLoad(sys);
            break;
        case 2: {
            cout << "Enter course code (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            faculty.viewClassList(sys, courseId);
            break;
        }
        case 3: {
            cout << "Enter student ID (0 = Back): ";
            cin >> studentId;
            if (studentId == "0") { cout << "Cancelled.\n"; break; }
            cout << "Enter course code (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            float marks;
            cout << "Enter marks (0-100): ";
            cin >> marks;
            faculty.enterGrades(sys, studentId, courseId, marks);
            sys.saveAll();
            break;
        }
        case 4: {
            cout << "Enter course code (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            faculty.viewClassSchedule(sys, courseId);
            break;
        }
        case 5: {
            cout << "Enter course code (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            faculty.manageCourseMaterials(sys, courseId);
            break;
        }
        case 6: {
            cout << "Enter student ID (0 = Back): ";
            cin >> studentId;
            if (studentId == "0") { cout << "Cancelled.\n"; break; }
            cout << "Enter course code (0 = Back): ";
            cin >> courseId;
            if (courseId == "0") { cout << "Cancelled.\n"; break; }
            faculty.enterGradesDetailed(sys, studentId, courseId);
            sys.saveAll();
            break;
        }
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

int main() {
    System sys;
    Admin admin("100", "Ishtiak Ahmed", "123", &sys);

    cout << "=== University System ===\n";
    sys.loadAll();

    int choice = -1;
    while (true) {
        cout << "\n---- Main Menu ----\n";
        cout << "1. Admin login\n";
        cout << "2. Student signup\n";
        cout << "3. Student login\n";
        cout << "4. Faculty signup\n";
        cout << "5. Faculty login\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            cout << "Exiting and saving data...\n";
            sys.saveAll();
            break;
        }

        string id, name, pass;
        switch (choice) {
        case 1: {
            string adminId;
            cout << "\n--- Admin Login ---\n";
            cout << "Enter admin ID (0 = Back): ";
            cin >> adminId;
            if (adminId == "0") { cout << "Back.\n"; break; }
            cout << "Enter password (0 = Back): ";
            cin >> pass;
            if (pass == "0") { cout << "Back.\n"; break; }
            if (adminId == "100" && admin.login(pass)) {
                cout << "Admin login successful.\n";
                adminMenu(sys, admin);
            } else {
                cout << "Invalid admin credentials.\n";
            }
            break;
        }
        case 2: {
            cout << "\n--- Student Signup ---\n";
            cout << "Enter your admin-assigned student ID (0 = Back): ";
            cin >> id;
            if (id == "0") { cout << "Back.\n"; break; }
            Student* s = findStudent(sys, id);
            if (!s) {
                cout << "ID not found. Contact admin to be added first.\n"; break;
            }
            if (s->getPassword() != "") {
                cout << "Already signed up. Please login instead.\n"; break;
            }
            string dept;
            cout << "Enter your department (e.g. CSE): ";
            cin >> dept;
            if (dept == "0") { cout << "Back.\n"; break; }
            s->setDepartment(dept);
            cout << "Set your password (0 = Back): ";
            cin >> pass;
            if (pass == "0") { cout << "Back.\n"; break; }
            s->setPassword(pass);
            sys.saveAll();
            cout << "Signup successful.\n";
            break;
        }
        case 3: {
            cout << "\n--- Student Login ---\n";
            cout << "Enter student ID (0 = Back): ";
            cin >> id;
            if (id == "0") { cout << "Back.\n"; break; }
            cout << "Enter password (0 = Back): ";
            cin >> pass;
            if (pass == "0") { cout << "Back.\n"; break; }
            Student* s = findStudent(sys, id);
            if (!s || !s->checkPassword(pass)) {
                cout << "Invalid credentials.\n"; break;
            }
            cout << "Student login successful.\n";
            studentMenu(sys, admin, *s);
            break;
        }
        case 4: {
            cout << "\n--- Faculty Signup ---\n";
            cout << "Enter your admin-assigned faculty ID (0 = Back): ";
            cin >> id;
            if (id == "0") { cout << "Back.\n"; break; }
            Faculty* f = findFaculty(sys, id);
            if (!f) {
                cout << "ID not found. Contact admin to be added first.\n"; break;
            }
            if (!f->getPassword().empty()) {
                cout << "Already signed up. Please login instead.\n"; break;
            }
            cout << "Set your password (0 = Back): ";
            cin >> pass;
            if (pass == "0") { cout << "Back.\n"; break; }
            f->setPassword(pass);
            sys.saveAll();
            cout << "Signup successful.\n";
            break;
        }
        case 5: {
            cout << "\n--- Faculty Login ---\n";
            cout << "Enter faculty ID (0 = Back): ";
            cin >> id;
            if (id == "0") { cout << "Back.\n"; break; }
            cout << "Enter password (0 = Back): ";
            cin >> pass;
            if (pass == "0") { cout << "Back.\n"; break; }
            Faculty* f = findFaculty(sys, id);
            if (!f || !f->checkPassword(pass)) {
                cout << "Invalid credentials.\n"; break;
            }
            cout << "Faculty login successful.\n";
            facultyMenu(sys, *f);
            break;
        }
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
    return 0;
}