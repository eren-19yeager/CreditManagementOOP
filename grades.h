#ifndef GRADES_H
#define GRADES_H

#include <string>
using namespace std;

class CourseComponent; // forward declaration

class Grades {
public:
    string studentID;
    string courseCode;
    float  marks;     // final computed result (0-100)
    string letter;    // A / B / C / D / F

    CourseComponent* component; // nullptr = simple entry, non-null = detailed breakdown

    Grades();
    Grades(string sid, string code, float m);                         // simple marks
    Grades(string sid, string code, CourseComponent* comp);           // component-based

    void computeGrade();
    void display() const;
};

#endif