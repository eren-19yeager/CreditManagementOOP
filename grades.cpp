#include "grades.h"
#include "CourseComponent.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

Grades::Grades()
    : studentID(""), courseCode(""), marks(0), letter("F"), component(nullptr) {}

// Simple marks constructor (backwards compatible)
Grades::Grades(string sid, string code, float m)
    : studentID(sid), courseCode(code), marks(m), component(nullptr) {
    computeGrade();
}

// Component-based constructor
Grades::Grades(string sid, string code, CourseComponent* comp)
    : studentID(sid), courseCode(code), component(comp) {
    if (comp) {
        marks = comp->getResult();
    } else {
        marks = 0;
    }
    computeGrade();
}

void Grades::computeGrade() {
    if      (marks >= 80) letter = "A";
    else if (marks >= 70) letter = "B";
    else if (marks >= 60) letter = "C";
    else if (marks >= 50) letter = "D";
    else                  letter = "F";
}

void Grades::display() const {
    cout << courseCode << " : " << marks << " (" << letter << ")";
    if (component) {
        cout << "\n";
        component->displayStatus();
    } else {
        cout << "\n";
    }
}
// Serialization
void Grades::serialize(ofstream &out) const
{
    out << left
        << setw(12) << studentID << " | "
        << setw(12) << courseCode << " | "
        << setw(8)  << fixed << setprecision(2) << marks << " | "
        << setw(3)  << letter
        << endl;
}
Grades Grades::deserialize(const string &line)
{
    stringstream ss(line);

    string sid, code, letter;
    float marks;

    ss >> sid;
    ss.ignore(3);

    ss >> code;
    ss.ignore(3);

    ss >> marks;
    ss.ignore(3);

    ss >> letter;

    return Grades(sid, code, marks);
}
