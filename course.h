#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

using namespace std;

class CourseComponent;

class Course {
private:
    string courseID;
    string courseTitle;
    string courseType;
    int credits;

    int capacity;
    int enrolledCount;

    string instructorID;
    vector<string> prerequisites;

    CourseComponent* component;   // SINGLE component now

public:
    Course(string id = "", 
           string title = "", 
           string type = "Core", 
           int credit = 3, 
           int cap = 30);

    string getCourseID() const;
    string getCourseTitle() const;
    string getCourseType() const;
    int getCredits() const;
    int getCapacity() const;
    int getEnrolledCount() const;
    string getInstructorID() const;

    void setInstructor(string instructorID);
    void addPrerequisite(string prereqID);

    bool isSeatAvailable() const;
    bool enrollStudent();
    bool dropStudent();

    bool checkPrerequisite(const vector<string>& completedCourses) const;

    void displayCourseInfo() const;

    // component handling
    void setComponent(CourseComponent* comp);
    CourseComponent* getComponent();
    float calculateCourseResult();

    void displayComponent() const;

    friend void compareEnrollment(const Course& c1, const Course& c2);
};

#endif
