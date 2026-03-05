#ifndef RESULTMANAGER_H
#define RESULTMANAGER_H

#include "Student.h"
#include "Enrollment.h"
#include <vector>

class ResultManager {
public:
    void generateResults(Student* student);   // triggers calculateResult()
    float calculateGPA(Student* student);     // computes CGPA
    void generateTranscript(Student* student); // prints transcript
};

#endif