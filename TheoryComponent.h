#ifndef THEORYCOMPONENT_H
#define THEORYCOMPONENT_H

#include "CourseComponent.h"

class TheoryComponent : virtual public CourseComponent {
private:
    float quizzes[4];
    float assignment;
    float midExam;
    float finalExam;

public:
    TheoryComponent();
    TheoryComponent(string id);

    void enroll();
    void setTheoryMarks(float q[], float assign, float mid, float finalM);
    void calculateResult();

    void   evaluate(float dummy = 0) override;
    string getComponentType()        const override;
    void   displayStatus()           const override;
    void   displayBreakdown()        const;

    ~TheoryComponent();
};

#endif