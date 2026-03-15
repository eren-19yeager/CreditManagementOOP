#include "labComponent.h"
#include <bits/stdc++.h>
LabComponent::LabComponent()
: CourseComponent("LAB"),
  project(0),
  dailyEval(0),
  written(0),
  finalLab(0)
{
}

LabComponent::LabComponent(string id)
: CourseComponent(id),
  project(0),
  dailyEval(0),
  written(0),
  finalLab(0)
{
}



void LabComponent::enroll()
{
    cout << "Lab Component "
         << componentID
         << " enrolled successfully.\n";
}



void LabComponent::setLabMarks(float p,
                               float d,
                               float w,
                               float f)
{
    project   = p;
    dailyEval = d;
    written   = w;
    finalLab  = f;

    cout << "Lab marks recorded for "
         << componentID << endl;
}



void LabComponent::evaluate(float)
{
    calculateResult();
    evaluated = true;

    cout << "Lab evaluation completed for "
         << componentID << endl;
}

void LabComponent::calculateResult()
{
    
    result = project + dailyEval + written + finalLab;
}



string LabComponent::getComponentType() const
{
    return "Laboratory Component";
}



void LabComponent::displayBreakdown() const
{
    cout << "\nLab Marks Breakdown\n";
    cout << "Project: " << project << "/30\n";
    cout << "Daily Evaluation: " << dailyEval << "/30\n";
    cout << "Written Test: " << written << "/20\n";
    cout << "Final Lab: " << finalLab << "/20\n";
}

void LabComponent::displayStatus() const
{
    cout << "\n===== LAB STATUS REPORT =====\n";

    cout << "Component ID: "
         << componentID << endl;

    cout << "Type: "
         << getComponentType() << endl;

    displayBreakdown();

    cout << "Total Result: "
         << result << "/100\n";

    cout << "Percentage: "
         << calculatePercentage()
         << "%\n";

    cout << "Evaluation Status: "
         << (evaluated ? "Completed" : "Pending")
         << endl;
}


LabComponent::~LabComponent()
{
    cout << "Destroying LabComponent: "
         << componentID << endl;
}