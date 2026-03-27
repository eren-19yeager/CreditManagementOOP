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
#include "Enrollment.h"
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

    // ---------- Template lookup ----------
    template <typename T>
    T* findByID(vector<T> &vec, const string &id) {
        for (auto &item : vec)
            if (item.getId() == id) return &item;
        return nullptr;
    }

    // ---------- Lookup ----------
    Student* findStudent(const string &studentID);
    Faculty* findFaculty(const string &facultyID);
    Course*  findCourse (const string &code);

    // ---------- Enrollment ----------
    bool enroll(const string &studentID, const string &courseCode,
                const string &semester = "");
    bool drop  (const string &studentID, const string &courseCode);

    // ---------- Grades ----------
    void assignGrade             (const string &studentID, const string &courseCode, float marks);
    void assignGradeFromComponent(const string &studentID, const string &courseCode,
                                  CourseComponent* comp);
    void calculateGPA(const string &studentID);

    // ---------- Credits & overload ----------
    void showCreditStatus        (const string &studentID);
    bool checkAndEnableOverload  (const string &studentID);
    void enableOverloadForStudent(const string &studentID);
    void resetSemesterForStudent (const string &studentID);

    // ---------- Prerequisites ----------
    void addPrerequisiteToCourse  (const string &courseCode, const string &prereqCode);
    void viewCoursePrerequisites  (const string &courseCode) const;
    bool checkStudentPrerequisites(const string &studentID,  const string &courseCode);
    void markCourseCompleted      (const string &studentID,  const string &courseCode);

    //-----table views-----
    void printStudentsTable() const;
    void printCoursesTable() const;
    void printGradesTable() const;
    
    // ---------- Views ----------
    void showGradesForStudent   (const string &studentID);
    void showScheduleForStudent (const string &studentID);
    void showScheduleForFaculty (const string &facultyID);
    void showProgress           (const string &studentID);

    vector<Course*> getAvailableCoursesForStudent(const string &studentID);
    void displayCourseDetails(const Course &c) const;

    // ---------- CSV ----------
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
