#ifndef LABCOMPONENT_H
#define LABCOMPONENT_H

#include "CourseComponent.h"

/*
    Represents laboratory-based evaluation.
    Components:
        Project (30)
        Daily Evaluation (30)
        Written (20)
        Final Lab (20)
*/

class LabComponent : virtual public CourseComponent {
private:
    float project;
    float dailyEval;
    float written;
    float finalLab;

public:

    // Constructors
    LabComponent();
    LabComponent(string id);

    // Core behaviour
    void enroll();
    void setLabMarks(float p, float d, float w, float f);

    // Overridden polymorphic behaviour
    void evaluate(float dummy = 0) override;
    void calculateResult();
    string getComponentType() const override;

    // Reporting
    void displayStatus() const override;
    void displayBreakdown() const;

    // Destructor
    ~LabComponent();
};

#endif