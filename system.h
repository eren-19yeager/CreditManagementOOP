#ifndef SYSTEM_H
#define SYSTEM_H

#include <bits/stdc++.h>
#include "student.h"
#include "faculty.h"
#include "CreditAccount.h"
#include "grades.h"
#include "progress.h"
#include "course.h"
#include "ResultManager.h"
#include "enrollment.h"
using namespace std;

class CourseComponent;

struct ScheduleEntry {
    string studentID;
    string courseCode;
    string dayTime;
};

class System {
public:
    int maxCreditsAllowed = 18;

    vector<Student>        students;
    vector<Faculty>        faculties;
    vector<Course>         courses;
    vector<Enrollment>     enrollments;
    vector<Grades>         grades;
    vector<ScheduleEntry>  scheduleEntries;
    vector<DegreeProgress> progress;

    ResultManager resultManager;

    // lookup
    Student* findStudent(const string &studentID);
    Faculty* findFaculty(const string &facultyID);
    Course*  findCourse (const string &code);

    // enrollment
    bool enroll(const string &studentID, const string &courseCode,
                const string &semester = "");
    bool drop  (const string &studentID, const string &courseCode);

    // grades
    void assignGrade             (const string &studentID, const string &courseCode, float marks);
    void assignGradeFromComponent(const string &studentID, const string &courseCode,
                                  CourseComponent* comp);
    void calculateGPA(const string &studentID);

    // prerequisites
    void addPrerequisiteToCourse  (const string &courseCode, const string &prereqCode);
    void viewCoursePrerequisites  (const string &courseCode) const;
    bool checkStudentPrerequisites(const string &studentID,  const string &courseCode);
    void markCourseCompleted      (const string &studentID,  const string &courseCode);

    // views
    void showGradesForStudent   (const string &studentID);
    void showScheduleForStudent (const string &studentID);
    void showScheduleForFaculty (const string &facultyID);
    void showProgress           (const string &studentID);

    vector<Course*> getAvailableCoursesForStudent(const string &studentID);
    void displayCourseDetails(const Course &c) const;

    // CSV persistence
    void saveStudents();      void loadStudents();
    void saveFaculties();     void loadFaculties();
    void saveCourses();       void loadCourses();
    void saveEnrollments();   void loadEnrollments();
    void saveGrades();        void loadGrades();
    void saveProgress();      void loadProgress();
    void savePrerequisites(); void loadPrerequisites();

    void saveAll();
    void loadAll();
};

#endif
