#ifndef ONLINECOMPONENT_H
#define ONLINECOMPONENT_H

#include "TheoryComponent.h"
#include "labComponent.h"

class OnlineComponent : public TheoryComponent, public LabComponent {
private:
    float theoryWeight;
    float labWeight;

public:
    OnlineComponent(string id);

    void enroll();
    void calculateResult();

    void   evaluate(float dummy = 0)      override;
    string getComponentType()             const override;
    void   displayStatus()                const override;
    void   displayIntegratedBreakdown()   const;

    ~OnlineComponent();
};

#endif
