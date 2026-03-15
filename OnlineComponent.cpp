#include "OnlineComponent.h"
#include <bits/stdc++.h>
using namespace std;

OnlineComponent::OnlineComponent(string id)
    : CourseComponent(id), TheoryComponent(id), LabComponent(id),
      theoryWeight(0.6f), labWeight(0.4f) {}

void OnlineComponent::enroll() {
    TheoryComponent::enroll();
    LabComponent::enroll();
    cout << "Online Component " << componentID << " fully enrolled.\n";
}

void OnlineComponent::calculateResult() {
    TheoryComponent::calculateResult();
    float theoryResult = result;

    LabComponent::calculateResult();
    float labResult = result;

    result = (theoryResult * theoryWeight) + (labResult * labWeight);
}

void OnlineComponent::evaluate(float) {
    calculateResult();
    evaluated = true;
    cout << "Online evaluation completed for " << componentID << "\n";
}

string OnlineComponent::getComponentType() const {
    return "Online Component (Theory + Lab)";
}

void OnlineComponent::displayIntegratedBreakdown() const {
    TheoryComponent::displayBreakdown();
    LabComponent::displayBreakdown();
    cout << "\nWeighting: Theory " << (theoryWeight * 100)
         << "% / Lab " << (labWeight * 100) << "%\n";
}

void OnlineComponent::displayStatus() const {
    cout << "\n===== ONLINE STATUS REPORT =====\n";
    cout << "Component ID: " << componentID        << "\n";
    cout << "Type: "         << getComponentType() << "\n";
    displayIntegratedBreakdown();
    cout << "Weighted Result:  " << result << "\n";
    cout << "Evaluation Status: " << (evaluated ? "Completed" : "Pending") << "\n";
}

OnlineComponent::~OnlineComponent() {
    cout << "Destroying OnlineComponent: " << componentID << "\n";
}