#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
#include <vector>
#include "timeslot.h"
using std::string;

enum class CourseType { Theory, Lab, Online };

class Course {
private:
    string code;
    string title;
    int    credits;
    string facultyID;
    int    capacity;          // max students (0 = unlimited)
    int    enrolledCount = 0; // current enrolled count
    TimeSlot  timeSlot;
    CourseType courseType;
    std::vector<string> equivalentCourseCodes;
    std::vector<string> prerequisiteCodes;    // for checkPrerequisite

public:
    Course();
    Course(string c, string t, int cr);

    string getCode()        const;
    string getTitle()       const;
    string getCourseTitle() const { return getTitle(); }
    int    getCredits()     const;
    int    getCapacity()    const;
    int    getEnrolledCount() const { return enrolledCount; }

    void assignFaculty(const string &fid);
    void setCapacity  (int cap);
    string getFacultyID() const;

    const TimeSlot& getTimeSlot() const;
    void setTimeSlot(const TimeSlot &ts);

    CourseType getCourseType()       const;
    void       setCourseType(CourseType type);
    string     getCourseTypeString() const;

    // Seat management
    bool isSeatAvailable() const;
    void enrollStudent();   // increments enrolledCount
    void dropStudent();     // decrements enrolledCount

    // Similar / equivalent courses
    void addEquivalentCourse(const string &courseCode);
    bool isSimilarTo        (const string &courseCode) const;
    std::vector<string> getSimilarCourseCodes() const;

    // Prerequisites
    void addPrerequisite(const string &courseCode);
    bool checkPrerequisite(const std::vector<string> &completedCourses) const;
    const std::vector<string>& getPrerequisiteCodes() const;

    bool operator==(const Course &other) const { return code == other.code; }
    bool operator< (const Course &other) const { return code < other.code; }

    // Stream output: prints course summary
    friend ostream& operator<<(ostream &os, const Course &c) {
        os << c.code << " - " << c.title
           << " (" << c.credits << " cr)";
        if (!c.facultyID.empty()) os << " | Faculty: " << c.facultyID;
        os << " | " << c.enrolledCount << "/" << c.capacity << " seats";
        return os;
    }
    friend void printCourseDetails(const Course &c);
    friend bool sameFaculty(const Course &a, const Course &b);
};

#endif
