#include "TheoryComponent.h"



TheoryComponent::TheoryComponent()
: CourseComponent("THEORY"),
  assignment(0),
  midExam(0),
  finalExam(0)
{
    for(int i=0;i<4;i++)
        quizzes[i] = 0;
}

TheoryComponent::TheoryComponent(string id)
: CourseComponent(id),
  assignment(0),
  midExam(0),
  finalExam(0)
{
    for(int i=0;i<4;i++)
        quizzes[i] = 0;
}



void TheoryComponent::enroll()
{
    cout << "Manual Theory Enrollment completed for "
         << componentID << endl;
}



void TheoryComponent::setTheoryMarks(float q[],
                                     float assign,
                                     float mid,
                                     float finalM)
{
    for(int i=0;i<4;i++)
        quizzes[i] = q[i];

    assignment = assign;
    midExam = mid;
    finalExam = finalM;

    cout << "Theory marks recorded for "
         << componentID << endl;
}



void TheoryComponent::evaluate(float)
{
    calculateResult();
    evaluated = true;

    cout << "Theory evaluation completed for "
         << componentID << endl;
}

void TheoryComponent::calculateResult()
{
    float quizTotal = 0;

    for(int i=0;i<4;i++)
        quizTotal += quizzes[i];

    float total =
        quizTotal +
        assignment +
        midExam +
        finalExam;     // total out of 300

    result = (total / 300.0f) * 100.0f;
}

/* ---------------- Polymorphic Identity ---------------- */

string TheoryComponent::getComponentType() const
{
    return "Theory Component";
}



void TheoryComponent::displayBreakdown() const
{
    cout << "\nTheory Marks Breakdown\n";

    for(int i=0;i<4;i++)
        cout << "Quiz " << i+1
             << ": " << quizzes[i] << endl;

    cout << "Assignment: " << assignment << endl;
    cout << "Mid Exam: " << midExam << endl;
    cout << "Final Exam: " << finalExam << endl;
}

void TheoryComponent::displayStatus() const
{
    cout << "\n===== THEORY STATUS REPORT =====\n";

    cout << "Component ID: "
         << componentID << endl;

    cout << "Type: "
         << getComponentType() << endl;

    displayBreakdown();

    cout << "Final Result: "
         << result << "%\n";

    cout << "Evaluation Status: "
         << (evaluated ? "Completed" : "Pending")
         << endl;
}



TheoryComponent::~TheoryComponent()
{
    cout << "Destroying TheoryComponent: "
         << componentID << endl;
}