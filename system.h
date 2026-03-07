#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <string>
#include "Student.h"
#include "Faculty.h"
#include "CreditAccount.h"
#include "grade.h"
#include "schedule.h"
#include "progress.h"
#include "course.h"

using namespace std;

// simple enrollment record
struct Enrollment {
    string studentID;
    string courseCode;
};

class System {
public:
    int maxCreditsAllowed = 18;  // used when creating students' credit accounts

    // people
    vector<Student> students;
    vector<Faculty> faculties;

    // courses
    vector<Course> courses;

    // enrollment
    vector<Enrollment> enrollments;

    // grades
    vector<Grade> grades;

    // schedule
    vector<Schedule> schedules;

    // progress
    vector<DegreeProgress> progress;

    // ---------- FUNCTIONS ----------
    void enroll(string studentID, string courseCode);
    void assignGrade(string studentID, string courseCode, float marks);
    void calculateGPA(string studentID);

    // student-level views using Grade / Schedule / DegreeProgress
    void showGradesForStudent(const string &studentID);
    void showScheduleForStudent(const string &studentID);
    void showProgress(const string &studentID);

    // file handling
    void saveCourses();
    void loadCourses();
};

#endif
