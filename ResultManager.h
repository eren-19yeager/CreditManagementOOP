#ifndef RESULTMANAGER_H
#define RESULTMANAGER_H

#include <vector>
#include "grades.h"
using namespace std;

class ResultManager {
private:
    vector<Grades> internalGrades; // synced copy for internal use

public:
    void  addGrade          (const string& studentID, const string& courseCode, float marks);
    float calculateGPA      (const vector<Grades>& grades, string studentID);
    void  generateTranscript(const vector<Grades>& grades, string studentID);
};

#endif
