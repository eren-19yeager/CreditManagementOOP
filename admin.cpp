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

void Admin::display() {
    cout << "Admin : " << id << " " << name << endl;
}

bool Admin::login(string pass) {
    return pass == password;
}

void Admin::addStudent(string id, string name) {
    sys->students.push_back(Student(id, name, sys->maxCreditsAllowed, 9));
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
    int credits = 0;
    for (auto &c : sys->courses) {
        if (c.getCode() == courseID) {
            credits = c.getCredits();
            break;
        }
    }
    for (auto &s : sys->students) {
        if (s.getId() == studentID) {
            s.enroll(courseID, credits);
            sys->enroll(studentID, courseID);
            return;
        }
    }
    cout << "Student or course not found.\n";
}

void Admin::assignFacultyToCourse(string facultyID, string courseID) {
    for (auto &c : sys->courses) {
        if (c.getCode() == courseID) {
            c.assignFaculty(facultyID);
            cout << "Faculty " << facultyID << " assigned to " << courseID << ".\n";
            return;
        }
    }
    cout << "Course not found.\n";
}

void Admin::setCreditLimit(int limit) {
    sys->maxCreditsAllowed = limit;
    cout << "Credit limit set to " << limit << " (for new students).\n";
}

void Admin::manageCapacity(string courseID, int newCapacity) {
    for (auto &c : sys->courses) {
        if (c.getCode() == courseID) {
            c.setCapacity(newCapacity);
            cout << "Capacity for " << courseID << " set to " << newCapacity << ".\n";
            return;
        }
    }
    cout << "Course not found.\n";
}

static void displayPerson(Person &p) {
    p.display();
}

void Admin::viewAll() {
    cout << "\nStudents:\n";
    for (auto &s : sys->students)
        displayPerson(s);

    cout << "\nFaculty:\n";
    for (auto &f : sys->faculties)
        displayPerson(f);

    cout << "\nCourses:\n";
    for (auto &c : sys->courses)
        cout << c.getCode() << " - " << c.getTitle()
             << " (" << c.getCredits() << " credits, capacity " << c.getCapacity() << ")\n";
}
