#include "CourseComponent.h"
#include <bits/stdc++.h>
using namespace std;

CourseComponent::CourseComponent()
    : componentID("NA"), result(0), fullMarks(100), evaluated(false) {}

CourseComponent::CourseComponent(string id, float full)
    : componentID(id), result(0), fullMarks(full), evaluated(false) {}

CourseComponent::CourseComponent(string id, float res, float full)
    : componentID(id), result(res), fullMarks(full), evaluated(true) {}

void CourseComponent::evaluate(float marks)
{
    if (marks < 0 || marks > fullMarks)
    {
        cout << "Invalid marks entered for " << componentID << "\n";
        return;
    }
    result = marks;
    evaluated = true;
    cout << "Component " << componentID << " evaluated successfully.\n";
}

float CourseComponent::calculatePercentage() const
{
    if (fullMarks == 0)
        return 0;
    return (result / fullMarks) * 100.0f;
}

void CourseComponent::displayStatus() const
{
    cout << "\nComponent Report\n";
    cout << "ID: " << componentID << "\n";
    cout << "Type: " << getComponentType() << "\n";
    cout << "Marks: " << result << "/" << fullMarks << "\n";
    cout << "Percentage: " << calculatePercentage() << "%\n";
    cout << "Status: " << (evaluated ? "Evaluated" : "Pending") << "\n";
}

void CourseComponent::resetMarks()
{
    result = 0;
    evaluated = false;
    cout << "Marks reset for " << componentID << "\n";
}

string CourseComponent::getComponentID() const { return componentID; }
float CourseComponent::getResult() const { return result; }
float CourseComponent::getFullMarks() const { return fullMarks; }
bool CourseComponent::isEvaluated() const { return evaluated; }

CourseComponent::~CourseComponent()
{
    cout << "Destroying CourseComponent: " << componentID << "\n";
}