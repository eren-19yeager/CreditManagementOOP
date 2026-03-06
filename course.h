#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

using namespace std;

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

    // Setters
    void setInstructor(string instructorID);
    void addPrerequisite(string prereqID);

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

};

#endif
