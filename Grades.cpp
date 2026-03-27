#include "grades.h"
#include "CourseComponent.h"
#include <iostream>
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
