#include "Admin.h"
#include "System.h"
#include "Student.h"
#include "Faculty.h"
#include "course.h"
#include <iostream>

using namespace std;

Admin::Admin(string id, string name, string pass, System *s)
    : Person(id, name, pass)
{
    password = pass;
    sys = s;
}

bool Admin::login(string pass) {
    return pass == password;
}

void Admin::addStudent(string id, string name) {
    sys->students.push_back(Student(id, name));
}

void Admin::addFaculty(string id, string name) {
    sys->faculties.push_back(Faculty(id, name));
}

void Admin::addCourse(string id, string name) {
    int credits;
    cout << "Enter credits for course " << id << " (" << name << "): ";
    cin >> credits;

    //Course object
    Course c(id, name, credits);
    sys->courses.push_back(c);
    cout << "Course added: " << id << " - " << name
         << " (" << credits << " credits)\n";
}

void Admin::enrollStudent(string studentID, string courseID) {
    for (auto &s : sys->students) {
        if (s.getId() == studentID) {
            s.enroll(courseID);
        }
    }
}

void Admin::viewAll() {
    cout << "\nStudents:\n";
    for (auto &s : sys->students)
        s.display();

    cout << "\nFaculty:\n";
    for (auto &f : sys->faculties)
        f.display();

    cout << "\nCourses:\n";
    for (auto &c : sys->courses)
        cout << c.getCode() << " - " << c.getTitle()
             << " (" << c.getCredits() << " credits)\n";
}