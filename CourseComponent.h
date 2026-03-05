#ifndef COURSECOMPONENT_H
#define COURSECOMPONENT_H

#include <iostream>
#include <string>
using namespace std;


class CourseComponent {
protected:
    string componentID;
    float result;
    float fullMarks;
    bool evaluated;

public:

   
    CourseComponent();
    CourseComponent(string id, float full = 100);
    CourseComponent(string id, float res, float full);

    
    virtual void evaluate(float marks);
    virtual float calculatePercentage() const;
    virtual string getComponentType() const = 0;

   
    virtual void displayStatus() const;
    virtual void resetMarks();

  
    string getComponentID() const;
    float getResult() const;
    float getFullMarks() const;
    bool isEvaluated() const;

    virtual ~CourseComponent();
};

#endif