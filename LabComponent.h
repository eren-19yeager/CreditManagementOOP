#ifndef LABCOMPONENT_H
#define LABCOMPONENT_H

#include "CourseComponent.h"

class LabComponent : virtual public CourseComponent {
private:
    float project;
    float dailyEval;
    float written;
    float finalLab;

public:
    LabComponent();
    LabComponent(string id);

    void enroll();
    void setLabMarks(float p, float d, float w, float f);
    void calculateResult();

    void   evaluate(float dummy = 0) override;
    string getComponentType()        const override;
    void   displayStatus()           const override;
    void   displayBreakdown()        const;

    ~LabComponent();
};

#endif
