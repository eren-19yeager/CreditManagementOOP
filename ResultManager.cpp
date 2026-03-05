#include "ResultManager.h"
#include "Grades.h"
#include "ResultContribution.h"
#include <iostream>

using namespace std;


void ResultManager::generateResults(Student* student) {
    vector<Enrollment*> enrolls = student->getEnrollments();

    for(auto e : enrolls) {
        if(e->getStatus() == "Completed") {
            e->getCourse()->getComponent()->calculateResult(); // polymorphic
        }
    }
}


float ResultManager::calculateGPA(Student* student) {
    vector<Enrollment*> enrolls = student->getEnrollments();
    ResultContribution total;

    for(auto e : enrolls) {
        if(e->getStatus() != "Completed") continue;

        Course* c = e->getCourse();
        float percentage = c->getComponent()->getResult();

        Grades g(percentage);

        ResultContribution current(
            g.getGPA() * c->getCredits(),
            c->getCredits()
        );

        total = total + current; // overloaded +
    }

    if(total.credits == 0) return 0;
    return total.creditGpa / total.credits;
}

// transcript 
void ResultManager::generateTranscript(Student* student) {
    cout << "\n===== TRANSCRIPT =====\n";
    const vector<Enrollment*>& enrolls = student->getEnrollments();

    for(auto e : enrolls) {
        if(e->getStatus() != "Completed") continue;

        Course* c = e->getCourse();
        float result = c->getComponent()->getResult();
        Grades g(result);

        cout << c->getCourseID()
             << " | Credits: " << c->getCredits()
             << " | Grade: " << g.getLetter()
             << " | GPA: " << g.getGPA()
             << endl;
    }

    cout << "FINAL CGPA: " << calculateGPA(student) << endl;
    cout << "=====================\n";
}