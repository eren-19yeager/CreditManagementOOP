#ifndef PROGRESS_H
#define PROGRESS_H

#include <bits/stdc++.h>
using std::string;

// Degree progress: semester, academic year, CG, semester finals (set by admin)
struct DegreeProgress {
    string studentID;
    int semester = 1;
    string academicYear = "";
    float CG = 0.0f;
    int semesterFinalsAttempted = 0;
    int semesterFinalsPassed = 0;
};

#endif

