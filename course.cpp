#include <iostream>
#include "course.h"
#include <iomanip>
#include <sstream>
#include <fstream>

Course::Course()
    : code(""), title(""), credits(0), facultyID(""),
      capacity(0), enrolledCount(0), courseType(CourseType::Theory) {}

Course::Course(string c, string t, int cr)
    : code(c), title(t), credits(cr), facultyID(""),
      capacity(30), enrolledCount(0), courseType(CourseType::Theory) {}

string Course::getCode()     const { return code; }
string Course::getTitle()    const { return title; }
int    Course::getCredits()  const { return credits; }
int    Course::getCapacity() const { return capacity; }

void   Course::setCapacity(int cap) { capacity = cap; }
void   Course::assignFaculty(const string &fid) { facultyID = fid; }
string Course::getFacultyID() const { return facultyID; }

const TimeSlot& Course::getTimeSlot() const { return timeSlot; }
void            Course::setTimeSlot(const TimeSlot &ts) { timeSlot = ts; }

CourseType Course::getCourseType() const { return courseType; }
void       Course::setCourseType(CourseType type) { courseType = type; }

string Course::getCourseTypeString() const {
    switch (courseType) {
        case CourseType::Theory: return "Theory";
        case CourseType::Lab:    return "Lab";
        case CourseType::Online: return "Online";
        default:                 return "Theory";
    }
}

// ---------- Seat management ----------

bool Course::isSeatAvailable() const {
    if (capacity <= 0) return true;       // 0 = unlimited
    return enrolledCount < capacity;
}

void Course::enrollStudent() {
    enrolledCount++;
}

void Course::dropStudent() {
    if (enrolledCount > 0) enrolledCount--;
}

// ---------- Similar / equivalent courses ----------

void Course::addEquivalentCourse(const string &courseCode) {
    if (courseCode != code)
        equivalentCourseCodes.push_back(courseCode);
}

bool Course::isSimilarTo(const string &courseCode) const {
    if (courseCode == code) return true;
    for (const auto &eq : equivalentCourseCodes)
        if (eq == courseCode) return true;
    return false;
}

std::vector<string> Course::getSimilarCourseCodes() const {
    std::vector<string> result;
    result.push_back(code);
    for (const auto &eq : equivalentCourseCodes)
        result.push_back(eq);
    return result;
}

// ---------- Prerequisites ----------

void Course::addPrerequisite(const string &courseCode) {
    prerequisiteCodes.push_back(courseCode);
}

bool Course::checkPrerequisite(const std::vector<string> &completedCourses) const {
    for (const auto &pre : prerequisiteCodes) {
        bool found = false;
        for (const auto &done : completedCourses)
            if (done == pre) { found = true; break; }
        if (!found) return false;
    }
    return true;
}

const std::vector<string>& Course::getPrerequisiteCodes() const {
    return prerequisiteCodes;
}

// ---------- Friend functions ----------

// Directly accesses private members: code, title, credits, facultyID,
// capacity, enrolledCount, courseType, timeSlot
void printCourseDetails(const Course &c) {
    std::cout << "Code: "     << c.code
              << " | Title: " << c.title
              << " | Credits: "<< c.credits
              << " | Faculty: "<< (c.facultyID.empty() ? "Unassigned" : c.facultyID)
              << " | Seats: "  << c.enrolledCount << "/" << c.capacity
              << " | Type: "   << c.getCourseTypeString();
    if (!c.timeSlot.getDay().empty())
        std::cout << " | " << c.timeSlot.getDay()
                  << " " << c.timeSlot.getStartTimeStr()
                  << "-" << c.timeSlot.getEndTimeStr();
    std::cout << "\n";
}
//Serialization
void Course::serialize(ofstream &out) const
{
    out << left
        << setw(10) << code << " | "
        << setw(25) << title << " | "
        << setw(5)  << credits << " | "
        << setw(10) << getCourseTypeString() << " | "
        << setw(10) << facultyID
        << endl;
}
Course Course::deserialize(const string &line)
{
    stringstream ss(line);

    string code, title, type, faculty;
    int credits;

    ss >> code;
    ss.ignore(3);

    getline(ss, title, '|');
    title = title.substr(0, title.size() - 1);

    ss >> credits;
    ss.ignore(3);

    ss >> type;
    ss.ignore(3);

    ss >> faculty;

    Course c(code, title, credits);
    c.assignFaculty(faculty);

    if (type == "Lab") c.setCourseType(CourseType::Lab);
    else if (type == "Online") c.setCourseType(CourseType::Online);

    return c;
}

// Directly accesses private member facultyID to compare two courses
bool sameFaculty(const Course &a, const Course &b) {
    return !a.facultyID.empty() && a.facultyID == b.facultyID;
}
