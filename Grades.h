#ifndef GRADES_H
#define GRADES_H

#include <string>
#include <iostream>
using namespace std;

class CourseComponent;

class Grades {
public:
    string studentID;
    string courseCode;
    float  marks;
    string letter;

    CourseComponent* component;

    Grades();
    Grades(string sid, string code, float m);
    Grades(string sid, string code, CourseComponent* comp);

    void computeGrade();
    void display() const;

    // Sort grades by marks (highest first)
    bool operator< (const Grades &other) const { return marks >  other.marks; }
    bool operator==(const Grades &other) const {
        return studentID == other.studentID && courseCode == other.courseCode;
    }

    //Serialization
    void serialize(ofstream &out) const;
    static Grades deserialize(const string &line);

    // Stream output: prints "courseCode : marks (letter)"
    friend ostream& operator<<(ostream &os, const Grades &g) {
        os << g.courseCode << " : " << g.marks << " (" << g.letter << ")";
        return os;
    }
};

#endif
