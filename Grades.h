#ifndef GRADES_H
#define GRADES_H
#include <string>
using namespace std;

class Grades {
private:
    float percentage;
    float gradePoint;
    string letter;

public:
    Grades(float p = 0);

    void computeGrade();

    float getGPA() const;
    string getLetter() const;
};

#endif