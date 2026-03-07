#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "Timeslot.h"

using namespace std;

class CourseComponent;   // forward declaration

class Course {
private:
    string courseID;
    string courseTitle;
    string courseType;   // Core / Elective
    int credits;

    int capacity;
    int enrolledCount;

    string instructorID;
    vector<string> prerequisites;
    vector<CourseComponent*> components;
    TimeSlot scheduleSlot;

public:
    // Constructor
    Course(string id = "", 
           string title = "", 
           string type = "Core", 
           int credit = 3, 
           int cap = 30);

    // Getters
    string getCourseID() const;
    string getCourseTitle() const;
    string getCourseType() const;
    int getCredits() const;
    int getCapacity() const;
    int getEnrolledCount() const;
    string getInstructorID() const;
    TimeSlot getTimeSlot() const;        

    // Setters
    void setInstructor(string instructorID);
    void addPrerequisite(string prereqID);
    void setTimeSlot(const TimeSlot& slot);

    // Enrollment Management
    bool isSeatAvailable() const;
    bool enrollStudent();
    bool dropStudent();

    // Prerequisite Checking
    bool checkPrerequisite(const vector<string>& completedCourses) const;

    // Utility
    void displayCourseInfo() const;
    void addComponent(CourseComponent* comp);
    void displayComponents() const;

    // NEW FUNCTIONS (added)
    vector<CourseComponent*>& getComponents();
    float calculateCourseResult();

    friend void compareEnrollment(const Course& c1, const Course& c2);
};

#endif
