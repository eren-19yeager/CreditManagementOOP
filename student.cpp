#include <iomanip>
#include <sstream>
#include <fstream>
#include "student.h"
#include "system.h"
#include <bits/stdc++.h>
using namespace std;

// ---------- Constructors ----------
Student::Student() : Person("", "", ""), creditAccount(18, 9) {}

Student::Student(string id, string name, string pass, string sec, string dept,
                 int maxCredits, int minCredits)
    : Person(id, name, pass), creditAccount(maxCredits, minCredits),
      section(sec), department(dept) {}

Student::Student(string id, string name, string pass, int maxCredits, int minCredits)
    : Person(id, name, pass), creditAccount(maxCredits, minCredits) {}

// ---------- Getters / Setters ----------
string Student::getDepartment() const { return department; }
string Student::getSection()    const { return section; }
void   Student::setDepartment(const string &dept) { department = dept; }
void   Student::setSection   (const string &sec)  { section    = sec; }

CreditAccount& Student::getCreditAccount() { return creditAccount; }

const vector<string>& Student::getCourses()          const { return courses; }
const vector<string>& Student::getCompletedCourses() const { return completedCourses; }
void Student::addCompletedCourse(const string &courseCode) {
    completedCourses.push_back(courseCode);
}

// ---------- Enrollment ----------
bool Student::enroll(const string &courseID, int courseCredits) {
    for (const auto &c : courses)
        if (c == courseID) return false;   // already enrolled

    if (courseCredits <= 0) {
        // Credits handled externally (e.g. by Enrollment::enroll)
        courses.push_back(courseID);
        return true;
    }
    if (!creditAccount.canAddCourse(courseCredits)) {
        cout << "Cannot enroll: credit limit would be exceeded (current: "
             << creditAccount.getCurrentCredits()
             << ", max: " << creditAccount.getMaxCredits() << ").\n";
        return false;
    }
    courses.push_back(courseID);
    creditAccount.addCredits(courseCredits);
    return true;
}

void Student::dropCourse(const string &courseID, int courseCredits) {
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

// ---------- Views ----------
void Student::viewGrades  (System &sys) { cout << "\n--- Your Grades ---\n";     sys.showGradesForStudent(id); }
void Student::viewSchedule(System &sys) { cout << "\n--- Your Schedule ---\n";   sys.showScheduleForStudent(id); }
void Student::viewProgress(System &sys) { cout << "\n--- Degree Progress ---\n"; sys.showProgress(id); }
void Student::calculateGPA(System &sys) { cout << "\n--- GPA ---\n";             sys.calculateGPA(id); }

// ---------- Profile ----------
void Student::manageProfile() {
    cout << "\nProfile Info:\n";
    cout << "ID:   " << id   << "\n";
    cout << "Name: " << name << "\n";

    char ch;
    cout << "Update name? (y/n): ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        cin.ignore();
        cout << "Enter new name: ";
        getline(cin, name);
        cout << "Name updated.\n";
    }
    cout << "Update ID? (y/n): ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        cout << "Enter new ID: ";
        cin >> id;
        cout << "ID updated.\n";
    }
    cout << "Update Section? (y/n): ";
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        string sec;
        cout << "Enter new Section: ";
        cin >> sec;
        setSection(sec);
        cout << "Section updated.\n";
    }
}

void Student::viewProfile() const {
    cout << "\nProfile Info:\n";
    cout << "ID:         " << id << "\n";
    cout << "Name:       " << name << "\n";
    cout << "Department: " << (department.empty() ? "Not set" : department) << "\n";
    cout << "Section:    " << (section.empty()    ? "Not set" : section)    << "\n";
    cout << "Enrolled Courses: ";
    if (courses.empty()) cout << "None";
    else for (const auto &c : courses) cout << c << " ";
    cout << "\n";
}

void Student::viewEnrolledCourses() const {
    cout << "\nEnrolled Courses: ";
    if (courses.empty()) cout << "None";
    else for (const auto &c : courses) cout << c << " ";
    cout << "\n";
}

// ---------- Display ----------
void Student::display() {
    cout << "StudentID: " << id << "  Name: " << name << "\n";
    cout << "Courses: ";
    for (const auto &c : courses) cout << c << " ";
    cout << "\nDepartment: " << (department.empty() ? "Not set" : department) << "\n";
    cout << "Section:    " << (section.empty()    ? "Not set" : section)    << "\n\n";
}

void Student::display() const {
    cout << "StudentID: " << id << "  Name: " << name << "\n";
    cout << "Courses: ";
    for (const auto &c : courses) cout << c << " ";
    cout << "\nDepartment: " << (department.empty() ? "Not set" : department) << "\n";
    cout << "Section:    " << (section.empty()    ? "Not set" : section)    << "\n\n";
}

void Student::serialize(ofstream &out) const
{
    out << left
        << setw(10) << id << " | "
        << setw(20) << name << " | "
        << setw(10) << department << " | "
        << setw(10) << section
        << endl;
}

Student Student::deserialize(const string &line)
{
    stringstream ss(line);

    string id, name, dept, sec;

    ss >> id;
    ss.ignore(3);

    getline(ss, name, '|');
    name = name.substr(0, name.size() - 1);

    ss >> dept;
    ss.ignore(3);

    ss >> sec;

    return Student(id, name, "", sec, dept, 18, 9);
}
