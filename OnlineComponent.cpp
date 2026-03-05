#include "OnlineComponent.h"


OnlineComponent::OnlineComponent(string id)
: CourseComponent(id),
  TheoryComponent(id),
  LabComponent(id),
  theoryWeight(0.7f),
  labWeight(0.3f)
{
}



void OnlineComponent::enroll()
{
    cout << "Online Integrated Enrollment completed for "
         << componentID << endl;
}



void OnlineComponent::evaluate(float)
{
    calculateResult();
    evaluated = true;

    cout << "Online integrated evaluation completed for "
         << componentID << endl;
}

void OnlineComponent::calculateResult()
{
    

    TheoryComponent::calculateResult();
    float theoryRes = TheoryComponent::getResult();

    LabComponent::calculateResult();
    float labRes = LabComponent::getResult();

   
    result = theoryRes * theoryWeight +
             labRes * labWeight;
}



string OnlineComponent::getComponentType() const
{
    return "Online Integrated Component";
}



void OnlineComponent::displayIntegratedBreakdown() const
{
    cout << "\nIntegrated Evaluation Breakdown\n";

    cout << "Theory Weight: "
         << theoryWeight * 100 << "%\n";

    cout << "Lab Weight: "
         << labWeight * 100 << "%\n";
}

void OnlineComponent::displayStatus() const
{
    cout << "\n===== ONLINE COMPONENT REPORT =====\n";

    cout << "Component ID: "
         << componentID << endl;

    cout << "Type: "
         << getComponentType() << endl;

    displayIntegratedBreakdown();

    cout << "Final Combined Result: "
         << result << "%\n";

    cout << "Evaluation Status: "
         << (evaluated ? "Completed" : "Pending")
         << endl;
}



OnlineComponent::~OnlineComponent()
{
    cout << "Destroying OnlineComponent: "
         << componentID << endl;
}