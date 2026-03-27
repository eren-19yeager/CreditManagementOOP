#include "system.h"
#include "ScheduleManager.h"
#include "ResultManager.h"
#include "grades.h"
#include "CourseComponent.h"
#include "schedule.h"
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

// ---------- Lookup helpers ----------

Student* System::findStudent(const string &studentID) {
    return findByID(students, studentID);   // template findByID<Student>
}
Faculty* System::findFaculty(const string &facultyID) {
    return findByID(faculties, facultyID);  // template findByID<Faculty>
}

Course* System::findCourse(const string &code) {
    for (auto &c : courses)
        if (c.getCode() == code) return &c;
    return nullptr;
}

// ---------- Available courses ----------

vector<Course*> System::getAvailableCoursesForStudent(const string &studentID) {
    vector<string> enrolledCodes;
    for (const auto &e : enrollments)
        if (e.getStudentID() == studentID)
            enrolledCodes.push_back(e.getCourseCode());

    vector<Course*> available;
    for (auto &c : courses) {
        bool canEnroll = true;
        for (const auto &ec : enrolledCodes) {
            if (c.isSimilarTo(ec)) { canEnroll = false; break; }
        }
        if (!canEnroll) continue;
        if (!c.isSeatAvailable()) continue;
        // Filter out courses that would cause a time conflict
        const TimeSlot& newSlot = c.getTimeSlot();
        if (!newSlot.getDay().empty() && newSlot.getEndMinutes() > newSlot.getStartMinutes()) {
            bool hasConflict = false;
            for (const auto &e : enrollments) {
                if (e.getStudentID() != studentID || e.getStatus() != "Active") continue;
                Course* enrolled = findCourse(e.getCourseCode());
                if (!enrolled) continue;
                const TimeSlot& existing = enrolled->getTimeSlot();
                if (existing.getDay().empty()) continue;
                if (newSlot.conflictsWith(existing)) { hasConflict = true; break; }
            }
            if (hasConflict) continue;
        }
        available.push_back(&c);
    }
    return available;
}

// ---------- Display course details ----------

void System::displayCourseDetails(const Course &c) const {
    int enrolledCount = 0;
    for (const auto &e : enrollments)
        if (e.getCourseCode() == c.getCode()) enrolledCount++;

    cout << "\n--- Course Details ---\n";
    cout << "Code:     " << c.getCode()            << "\n";
    cout << "Title:    " << c.getTitle()            << "\n";
    cout << "Credits:  " << c.getCredits()          << "\n";
    cout << "Type:     " << c.getCourseTypeString() << "\n";
    cout << "Capacity: " << enrolledCount << "/" << c.getCapacity() << "\n";

    const TimeSlot &ts = c.getTimeSlot();
    if (!ts.getDay().empty() && (ts.getEndMinutes() > 0 || ts.getStartMinutes() > 0)) {
        string endStr = ts.getEndTimeStr();
        if (ts.getEndMinutes() == 0 && ts.getStartMinutes() > 0) {
            int endMin = ts.getStartMinutes() + c.getCredits() * 30;
            endStr = to_string(endMin / 60) + ":" +
                     (endMin % 60 < 10 ? "0" : "") + to_string(endMin % 60);
        }
        cout << "Schedule: " << ts.getDay() << " "
             << ts.getStartTimeStr() << "-" << endStr << "\n";
    } else {
        cout << "Schedule: Not set\n";
    }
    cout << "----------------------\n";
}

// ---------- Enroll ----------

bool System::enroll(const string &studentID, const string &courseCode,
                    const string &semester) {
    Student* st = findStudent(studentID);
    Course*  co = findCourse(courseCode);

    if (!st) { cout << "Student not found.\n";  return false; }
    if (!co) { cout << "Course not found.\n";   return false; }

    // Duplicate check
    for (const auto &e : enrollments)
        if (e.getStudentID() == studentID && e.getCourseCode() == courseCode) {
            cout << "Already enrolled in " << courseCode << ".\n";
            return false;
        }

    // ---- Time conflict check ----
    const TimeSlot& newSlot = co->getTimeSlot();
    if (!newSlot.getDay().empty() && newSlot.getEndMinutes() > newSlot.getStartMinutes()) {
        for (const auto &e : enrollments) {
            if (e.getStudentID() != studentID || e.getStatus() != "Active") continue;
            Course* enrolled = findCourse(e.getCourseCode());
            if (!enrolled) continue;
            const TimeSlot& existing = enrolled->getTimeSlot();
            if (existing.getDay().empty()) continue;
            if (newSlot.conflictsWith(existing)) {
                cout << "Schedule conflict: " << courseCode
                     << " (" << newSlot.getDay() << " "
                     << newSlot.getStartTimeStr() << "-" << newSlot.getEndTimeStr()
                     << ") clashes with already enrolled "
                     << e.getCourseCode()
                     << " (" << existing.getDay() << " "
                     << existing.getStartTimeStr() << "-" << existing.getEndTimeStr()
                     << ").\n";
                return false;
            }
        }
    }

    string eid = studentID + "_" + courseCode;
    Enrollment newEnrollment(eid, st, co, semester);
    if (!newEnrollment.enroll()) {
        cout << "Enrollment failed (seat/credit/prerequisite check).\n";
        return false;
    }

    enrollments.push_back(newEnrollment);
    return true;
}

// ---------- Drop ----------

bool System::drop(const string &studentID, const string &courseCode) {
    for (auto &e : enrollments) {
        if (e.getStudentID() == studentID && e.getCourseCode() == courseCode) {
            if (e.drop()) return true;
            cout << "Drop failed.\n";
            return false;
        }
    }
    cout << "Enrollment record not found.\n";
    return false;
}

// ---------- Grades ----------

void System::assignGrade(const string &studentID, const string &courseCode, float marks) {
    resultManager.addGrade(studentID, courseCode, marks);
    // Keep local grades vector in sync
    for (auto &g : grades) {
        if (g.studentID == studentID && g.courseCode == courseCode) {
            g = Grades(studentID, courseCode, marks);
            return;
        }
    }
    grades.push_back(Grades(studentID, courseCode, marks));
}

// Component-based grade
void System::assignGradeFromComponent(const string &studentID, const string &courseCode,
                                       CourseComponent* comp) {
    float marks = comp ? comp->getResult() : 0.0f;
    resultManager.addGrade(studentID, courseCode, marks);
    for (auto &g : grades) {
        if (g.studentID == studentID && g.courseCode == courseCode) {
            g = Grades(studentID, courseCode, comp); return;
        }
    }
    grades.push_back(Grades(studentID, courseCode, comp));
}

void System::calculateGPA(const string &studentID) {
    float gpa = resultManager.calculateGPA(grades, studentID);
    bool any = false;
    for (const auto &g : grades)
        if (g.studentID == studentID) { any = true; break; }
    if (!any) { cout << "No grades found.\n"; return; }
    cout << "GPA: " << gpa << "\n";
}

void System::showGradesForStudent(const string &studentID) {
    resultManager.generateTranscript(grades, studentID);
}

// ---------- Schedule ----------

void System::showScheduleForStudent(const string &studentID) {
    Student* st = findStudent(studentID);
    if (!st) { cout << "Student not found.\n"; return; }

    const vector<string>& courseIDs = st->getCourses();
    if (courseIDs.empty()) { cout << "\nNo courses enrolled.\n"; return; }

    cout << "\n--- Your Schedule (" << courseIDs.size() << " courses) ---\n";
    ScheduleManager mgr;
    Schedule schedule = mgr.generateSchedule(*st, *this);

    for (const auto &cid : courseIDs) {
        Course* c = findCourse(cid);
        if (!c) continue;
        const TimeSlot &ts = c->getTimeSlot();
        if (!ts.getDay().empty() && (ts.getEndMinutes() > 0 || ts.getStartMinutes() > 0)) {
            string endStr = ts.getEndTimeStr();
            if (ts.getEndMinutes() == 0 && ts.getStartMinutes() > 0) {
                int endMin = ts.getStartMinutes() + c->getCredits() * 30;
                endStr = to_string(endMin / 60) + ":" +
                         (endMin % 60 < 10 ? "0" : "") + to_string(endMin % 60);
            }
            cout << cid << " (" << c->getTitle() << "): "
                 << ts.getDay() << " " << ts.getStartTimeStr() << "-" << endStr << "\n";
        } else {
            cout << cid << " (" << c->getTitle() << "): Schedule not set\n";
        }
    }

    if (mgr.detectConflicts(schedule))
        cout << "  [Warning: conflicts detected in your schedule]\n";
    cout << "--------------------------------\n";
}

void System::showScheduleForFaculty(const string &facultyID) {
    cout << "\n--- Schedule entries for faculty " << facultyID << " ---\n";
    bool any = false;
    for (auto &s : scheduleEntries) {
        // Find if this course belongs to the faculty
        Course* c = findCourse(s.courseCode);
        if (c && c->getFacultyID() == facultyID) {
            cout << "  Course: " << s.courseCode
                 << "  Student: " << s.studentID
                 << "  Time: "    << s.dayTime << "\n";
            any = true;
        }
    }
    if (!any) cout << "  No schedule entries found.\n";
}

// ---------- Progress ----------

void System::showProgress(const string &studentID) {
    Student* st = findStudent(studentID);
    string dept = st ? st->getDepartment() : "";

    for (auto &p : progress) {
        if (p.studentID == studentID) {
            int cur = p.semesterFinalsPassed + 1;
            cout << "\n--- Degree Progress ---\n";
            cout << "Department: " << (dept.empty() ? "Not set" : dept) << "\n";
            cout << "Semester: "   << cur << "\n";
            cout << "Academic Year: " << (p.academicYear.empty() ? "Not set" : p.academicYear) << "\n";
            cout << "Semester finals attempted: " << p.semesterFinalsAttempted
                 << "  PASSED: " << p.semesterFinalsPassed << "\n";
            cout << "-----------------------\n";
            return;
        }
    }
    cout << "\n--- Degree Progress ---\n";
    cout << "Department: " << (dept.empty() ? "Not set" : dept) << "\n";
    cout << "No progress data yet.\n";
    cout << "-----------------------\n";
}

// ===================== CSV persistence =====================

void System::saveStudents() {
    ofstream file("students.csv");
    if (!file) { cout << "Error opening students.csv\n"; return; }
    file << "id,name,password,section,department\n";
    for (auto &s : students)
        file << s.getId() << "," << s.getName() << "," << s.getPassword() << ","
             << s.getSection() << "," << s.getDepartment() << "\n";
}

void System::loadStudents() {
    students.clear();
    ifstream file("students.csv");
    if (!file) return;
    string line;
    getline(file, line); // header
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, pass, sec, dept;
        getline(ss, id,   ',');
        getline(ss, name, ',');
        getline(ss, pass, ',');
        getline(ss, sec,  ',');
        getline(ss, dept, ',');
        if (id.empty()) continue;
        Student st(id, name, pass, maxCreditsAllowed, 9);
        if (!sec.empty())  st.setSection(sec);
        if (!dept.empty()) st.setDepartment(dept);
        students.push_back(st);
    }
}

void System::saveFaculties() {
    ofstream file("faculties.csv");
    if (!file) { cout << "Error opening faculties.csv\n"; return; }
    file << "id,name,password\n";
    for (auto &f : faculties)
        file << f.getId() << "," << f.getName() << "," << f.getPassword() << "\n";
}

void System::loadFaculties() {
    faculties.clear();
    ifstream file("faculties.csv");
    if (!file) return;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, pass;
        getline(ss, id,   ',');
        getline(ss, name, ',');
        getline(ss, pass, ',');
        if (id.empty()) continue;
        faculties.push_back(Faculty(id, name, pass));
    }
}

void System::saveCourses() {
    ofstream file("courses.csv");
    if (!file) { cout << "Error opening courses.csv\n"; return; }
    file << "code,title,credits,facultyID,capacity,enrolledCount,type,day,startMin,endMin\n";
    for (auto &c : courses) {
        const TimeSlot &ts = c.getTimeSlot();
        file << c.getCode()            << ","
             << c.getTitle()           << ","
             << c.getCredits()         << ","
             << c.getFacultyID()       << ","
             << c.getCapacity()        << ","
             << c.getEnrolledCount()   << ","
             << c.getCourseTypeString()<< ","
             << ts.getDay()            << ","
             << ts.getStartMinutes()   << ","
             << ts.getEndMinutes()     << "\n";
    }
}

void System::loadCourses() {
    courses.clear();
    ifstream file("courses.csv");
    if (!file) return;
    string line;
    getline(file, line); // header
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string code, title, credStr, fid, capStr, encStr, typeStr, dayStr, startStr, endStr;
        getline(ss, code,    ',');
        getline(ss, title,   ',');
        getline(ss, credStr, ',');
        getline(ss, fid,     ',');
        getline(ss, capStr,  ',');
        getline(ss, encStr,  ',');
        getline(ss, typeStr, ',');
        getline(ss, dayStr,  ',');
        getline(ss, startStr,',');
        getline(ss, endStr,  ',');
        if (code.empty()) continue;
        int credits = 0, capacity = 0, enrolled = 0, startMin = 0, endMin = 0;
        try {
            if (!credStr.empty())  credits  = stoi(credStr);
            if (!capStr.empty())   capacity = stoi(capStr);
            if (!encStr.empty())   enrolled = stoi(encStr);
            if (!startStr.empty()) startMin = stoi(startStr);
            if (!endStr.empty())   endMin   = stoi(endStr);
        } catch (...) { continue; }
        Course c(code, title, credits);
        if (!fid.empty())    c.assignFaculty(fid);
        if (capacity > 0)    c.setCapacity(capacity);
        for (int i = 0; i < enrolled; i++) c.enrollStudent(); // restore count
        if (typeStr == "Lab")    c.setCourseType(CourseType::Lab);
        else if (typeStr == "Online") c.setCourseType(CourseType::Online);
        if (!dayStr.empty() && endMin > startMin)
            c.setTimeSlot(TimeSlot(dayStr, startMin, endMin));
        courses.push_back(c);
    }
}

void System::saveEnrollments() {
    ofstream file("enrollments.csv");
    if (!file) { cout << "Error opening enrollments.csv\n"; return; }
    file << "enrollmentID,studentID,courseCode,semester,status\n";
    for (auto &e : enrollments)
        file << e.getEnrollmentID() << ","
             << e.getStudentID()    << ","
             << e.getCourseCode()   << ","
             << e.getSemester()     << ","
             << e.getStatus()       << "\n";
}

void System::loadEnrollments() {
    enrollments.clear();
    ifstream file("enrollments.csv");
    if (!file) return;
    string line;
    getline(file, line); // header
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string eid, sid, ccode, sem, status;
        getline(ss, eid,    ',');
        getline(ss, sid,    ',');
        getline(ss, ccode,  ',');
        getline(ss, sem,    ',');
        getline(ss, status, ',');
        if (sid.empty() || ccode.empty()) continue;

        Student* st = findStudent(sid);
        Course*  co = findCourse(ccode);
        if (!st || !co) continue;

        if (eid.empty()) eid = sid + "_" + ccode;
        Enrollment e(eid, st, co, sem);

        if (status == "Active" || status.empty()) {
            // Restore without re-running checks
            st->enroll(ccode, co->getCredits()); // updates student list + credits
            // enrolledCount on Course was already restored in loadCourses()
            e.restoreActive();
        } else if (status == "Dropped") {
            e.restoreDropped();
        } else if (status == "Completed") {
            e.complete();
        }
        enrollments.push_back(e);
    }
}

void System::saveGrades() {
    ofstream file("grades.csv");
    if (!file) { cout << "Error opening grades.csv\n"; return; }
    file << "studentID,courseCode,marks,letter\n";
    for (auto &g : grades)
        file << g.studentID << "," << g.courseCode << ","
             << g.marks     << "," << g.letter     << "\n";
}

void System::loadGrades() {
    grades.clear();
    ifstream file("grades.csv");
    if (!file) return;
    string line;
    getline(file, line); // header
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string sid, ccode, marksStr, letter;
        getline(ss, sid,      ',');
        getline(ss, ccode,    ',');
        getline(ss, marksStr, ',');
        getline(ss, letter,   ',');
        if (sid.empty() || ccode.empty() || marksStr.empty()) continue;
        float marks = 0.0f;
        try { marks = stof(marksStr); } catch (...) { continue; }
        grades.push_back(Grades(sid, ccode, marks));
        resultManager.addGrade(sid, ccode, marks); // sync ResultManager
    }
}

void System::saveProgress() {
    ofstream file("progress.csv");
    if (!file) return;
    file << "studentID,semester,academicYear,CG,finalsAttempted,finalsPassed\n";
    for (auto &p : progress)
        file << p.studentID << "," << p.semester << "," << p.academicYear << ","
             << p.CG << "," << p.semesterFinalsAttempted << ","
             << p.semesterFinalsPassed << "\n";
}

void System::loadProgress() {
    progress.clear();
    ifstream file("progress.csv");
    if (!file) return;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string sid, semStr, year, cgStr, attStr, passStr;
        getline(ss, sid,     ',');
        getline(ss, semStr,  ',');
        getline(ss, year,    ',');
        getline(ss, cgStr,   ',');
        getline(ss, attStr,  ',');
        getline(ss, passStr, ',');
        if (sid.empty()) continue;
        DegreeProgress p;
        p.studentID    = sid;
        p.academicYear = year;
        try {
            if (!semStr.empty())  p.semester               = stoi(semStr);
            if (!cgStr.empty())   p.CG                     = stof(cgStr);
            if (!attStr.empty())  p.semesterFinalsAttempted = stoi(attStr);
            if (!passStr.empty()) p.semesterFinalsPassed    = stoi(passStr);
        } catch (...) { continue; }
        progress.push_back(p);
    }
}



// ---------- Credit status & overload ----------

void System::showCreditStatus(const string &studentID) {
    Student* st = findStudent(studentID);
    if (!st) { cout << "Student not found.\n"; return; }
    CreditAccount& ca = st->getCreditAccount();
    cout << "\n--- Credit Status ---\n";
    cout << "Credits enrolled:  " << ca.getCurrentCredits() << "\n";
    cout << "Maximum allowed:   " << ca.getMaxCredits()
         << (ca.isOverloadAllowed() ? " (overload enabled)" : "") << "\n";
    cout << "Minimum required:  " << ca.getMinCredits()     << "\n";
    int remaining = ca.getMaxCredits() - ca.getCurrentCredits();
    cout << "Credits remaining: " << remaining              << "\n";
    if (ca.getCurrentCredits() < ca.getMinCredits())
        cout << "  [Warning: below minimum credit load!]\n";
    if (ca.isOverloadAllowed())
        cout << "  [Overload active: you may exceed the normal credit cap]\n";
    cout << "---------------------\n";
}

// Check GPA and enable overload if eligible (GPA >= 3.75)
bool System::checkAndEnableOverload(const string &studentID) {
    Student* st = findStudent(studentID);
    if (!st) { cout << "Student not found.\n"; return false; }
    float gpa = resultManager.calculateGPA(grades, studentID);
    bool eligible = st->getCreditAccount().checkOverloadEligibility(gpa);
    if (eligible)
        cout << "Overload enabled for " << studentID
             << " (GPA: " << gpa << " >= 3.75). "
             << "Credit cap is now lifted for this semester.\n";
    else
        cout << "Not eligible for overload (GPA: " << gpa
             << "). Requires GPA >= 3.75.\n";
    return eligible;
}

// Admin manually enables overload for a student
void System::enableOverloadForStudent(const string &studentID) {
    Student* st = findStudent(studentID);
    if (!st) { cout << "Student not found.\n"; return; }
    st->getCreditAccount().enableOverload();
    cout << "Overload manually enabled for " << studentID << ".\n";
}

// Reset semester credits (called at start of new semester)
void System::resetSemesterForStudent(const string &studentID) {
    Student* st = findStudent(studentID);
    if (!st) { cout << "Student not found.\n"; return; }
    st->getCreditAccount().resetSemesterCredits();
    cout << "Semester credits reset for " << studentID << ".\n";
}

// ===================== Prerequisites =====================

void System::addPrerequisiteToCourse(const string &courseCode, const string &prereqCode) {
    Course* c = findCourse(courseCode);
    if (!c) { cout << "Course " << courseCode << " not found.\n"; return; }
    Course* pre = findCourse(prereqCode);
    if (!pre) { cout << "Prerequisite course " << prereqCode << " not found.\n"; return; }
    c->addPrerequisite(prereqCode);
    cout << prereqCode << " added as prerequisite for " << courseCode << ".\n";
}

void System::viewCoursePrerequisites(const string &courseCode) const {
    const Course* c = nullptr;
    for (const auto &co : courses)
        if (co.getCode() == courseCode) { c = &co; break; }
    if (!c) { cout << "Course not found.\n"; return; }
    const vector<string>& prereqs = c->getPrerequisiteCodes();
    cout << "\n--- Prerequisites for " << courseCode << " (" << c->getTitle() << ") ---\n";
    if (prereqs.empty()) {
        cout << "  No prerequisites.\n";
    } else {
        for (const auto &p : prereqs) {
            cout << "  " << p;
            // show title if we can find it
            for (const auto &co : courses)
                if (co.getCode() == p) { cout << " - " << co.getTitle(); break; }
            cout << "\n";
        }
    }
    cout << "-------------------------------------------\n";
}

bool System::checkStudentPrerequisites(const string &studentID, const string &courseCode) {
    Student* st = findStudent(studentID);
    Course*  co = findCourse(courseCode);
    if (!st || !co) return false;

    const vector<string>& prereqs = co->getPrerequisiteCodes();
    if (prereqs.empty()) return true;

    const vector<string>& completed = st->getCompletedCourses();
    vector<string> missing;
    for (const auto &pre : prereqs) {
        bool found = false;
        for (const auto &done : completed)
            if (done == pre) { found = true; break; }
        if (!found) missing.push_back(pre);
    }
    if (missing.empty()) return true;

    cout << "Prerequisite check FAILED for " << studentID << " -> " << courseCode << ":\n";
    for (const auto &m : missing) {
        cout << "  Missing: " << m;
        for (const auto &co2 : courses)
            if (co2.getCode() == m) { cout << " (" << co2.getTitle() << ")"; break; }
        cout << "\n";
    }
    return false;
}

void System::markCourseCompleted(const string &studentID, const string &courseCode) {
    Student* st = findStudent(studentID);
    if (!st) { cout << "Student not found.\n"; return; }
    // avoid duplicates
    for (const auto &c : st->getCompletedCourses())
        if (c == courseCode) return;
    st->addCompletedCourse(courseCode);
    cout << courseCode << " marked as completed for " << studentID << ".\n";
}

// ===================== Prerequisite CSV =====================

void System::savePrerequisites() {
    ofstream file("prerequisites.csv");
    if (!file) { cout << "Error opening prerequisites.csv\n"; return; }
    file << "courseCode,prereqCode\n";
    for (const auto &c : courses) {
        for (const auto &p : c.getPrerequisiteCodes())
            file << c.getCode() << "," << p << "\n";
    }
}

void System::loadPrerequisites() {
    ifstream file("prerequisites.csv");
    if (!file) return;
    string line;
    getline(file, line); // header
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string ccode, pcode;
        getline(ss, ccode, ',');
        getline(ss, pcode, ',');
        if (ccode.empty() || pcode.empty()) continue;
        Course* c = findCourse(ccode);
        if (c) c->addPrerequisite(pcode);
    }
}

void System::saveAll() {
    saveStudents(); saveFaculties(); saveCourses();
    saveEnrollments(); saveGrades(); saveProgress();
    savePrerequisites();
}

void System::loadAll() {
    loadStudents(); loadFaculties(); loadCourses();
    loadEnrollments(); loadGrades(); loadProgress();
    loadPrerequisites();
}

void System::printStudentsTable() const
{
    cout << "\n--- Students ---\n";

    cout << left
         << setw(10) << "ID" << " | "
         << setw(20) << "Name" << " | "
         << setw(12) << "Department" << " | "
         << setw(10) << "Section" << endl;

    cout << "-------------------------------------------------------------\n";

    for (const auto &s : students)
    {
        cout << left
             << setw(10) << s.getId() << " | "
             << setw(20) << s.getName() << " | "
             << setw(12) << (s.getDepartment().empty() ? "N/A" : s.getDepartment()) << " | "
             << setw(10) << (s.getSection().empty() ? "N/A" : s.getSection())
             << endl;
    }
}
void System::printGradesTable() const
{
    cout << "\n--- Grades ---\n";

    cout << left
         << setw(12) << "StudentID" << " | "
         << setw(12) << "CourseCode" << " | "
         << setw(8)  << "Marks" << " | "
         << setw(6)  << "Grade" << endl;

    cout << "------------------------------------------------\n";

    for (const auto &g : grades)
    {
        cout << left
             << setw(12) << g.studentID << " | "
             << setw(12) << g.courseCode << " | "
             << setw(8)  << fixed << setprecision(2) << g.marks << " | "
             << setw(6)  << g.letter
             << endl;
    }
}
void System::printCoursesTable() const
{
    cout << "\n--- Courses ---\n";

    cout << left
         << setw(10) << "Code" << " | "
         << setw(25) << "Title" << " | "
         << setw(6)  << "Cr" << " | "
         << setw(10) << "Type" << " | "
         << setw(10) << "Faculty" << endl;

    cout << "--------------------------------------------------------------------------\n";

    for (const auto &c : courses)
    {
        cout << left
             << setw(10) << c.getCode() << " | "
             << setw(25) << c.getTitle() << " | "
             << setw(6)  << c.getCredits() << " | "
             << setw(10) << c.getCourseTypeString() << " | "
             << setw(10) << (c.getFacultyID().empty() ? "N/A" : c.getFacultyID())
             << endl;
    }
}
