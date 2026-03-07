#include "Course.h"
#include "CourseComponent.h"
#include <bits/stdc++.h>

using namespace std;

Course::Course(string id, string title, string type, int credit, int cap)
{
    courseID = id;
    courseTitle = title;
    courseType = type;
    credits = credit;
    capacity = cap;
    enrolledCount = 0;
    component = nullptr;
}

string Course::getCourseID() const { return courseID; }
string Course::getCourseTitle() const { return courseTitle; }
string Course::getCourseType() const { return courseType; }
int Course::getCredits() const { return credits; }
int Course::getCapacity() const { return capacity; }
int Course::getEnrolledCount() const { return enrolledCount; }
string Course::getInstructorID() const { return instructorID; }

void Course::setInstructor(string id)
{
    instructorID = id;
}

void Course::addPrerequisite(string prereqID)
{
    prerequisites.push_back(prereqID);
}

bool Course::isSeatAvailable() const
{
    return enrolledCount < capacity;
}

bool Course::enrollStudent()
{
    if(isSeatAvailable())
    {
        enrolledCount++;
        return true;
    }
    return false;
}

bool Course::dropStudent()
{
    if(enrolledCount > 0)
    {
        enrolledCount--;
        return true;
    }
    return false;
}

bool Course::checkPrerequisite(const vector<string>& completedCourses) const
{
    for(int i=0;i<prerequisites.size();i++)
    {
        bool found=false;

        for(int j=0;j<completedCourses.size();j++)
        {
            if(prerequisites[i]==completedCourses[j])
            {
                found=true;
                break;
            }
        }

        if(!found)
            return false;
    }

    return true;
}

void Course::displayCourseInfo() const
{
    cout<<"Course ID: "<<courseID<<endl;
    cout<<"Title: "<<courseTitle<<endl;
    cout<<"Type: "<<courseType<<endl;
    cout<<"Credits: "<<credits<<endl;
    cout<<"Instructor: "<<instructorID<<endl;
    cout<<"Seats: "<<enrolledCount<<"/"<<capacity<<endl;
}

void Course::setComponent(CourseComponent* comp)
{
    component = comp;
}

CourseComponent* Course::getComponent()
{
    return component;
}

float Course::calculateCourseResult()
{
    if(component == nullptr)
        return 0;

    component->evaluate(component->getResult());
    return component->getResult();
}

void Course::displayComponent() const
{
    if(component != nullptr)
        component->displayStatus();
}

void compareEnrollment(const Course& c1,const Course& c2)
{
    if(c1.enrolledCount>c2.enrolledCount)
        cout<<c1.courseTitle<<" has more students enrolled.\n";
    else if(c2.enrolledCount>c1.enrolledCount)
        cout<<c2.courseTitle<<" has more students enrolled.\n";
    else
        cout<<"Both courses have equal enrollment.\n";
}
