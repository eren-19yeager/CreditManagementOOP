#ifndef RESULTMANAGER_H
#define RESULTMANAGER_H

#include "student.h"
#include "enrollment.h"
#include "Course.h"
#include <vector>

using namespace std;

class ResultManager {
public:
    void generateResults(Student* student);      // triggers evaluation
    float calculateGPA(Student* student);        // computes CGPA
    void generateTranscript(Student* student);   // prints transcript
};

#endif
